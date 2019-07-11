#include "Matrix.h"


void Matrix::initialize()
{
#define CHK_ERROR if (erro != cudaSuccess) goto Error;

	auto erro = cudaMalloc(&gpu_matrix, sizeof(double) * sz);
	cpu_matrix = new double[sz];


	if (erro)
		Error: std::cerr << "Error on CUDA: " << cudaGetErrorString(erro);
}

bool Matrix::updateCPU() const
{
	//cudaMemcpy(device, host, bytes, cudaMemcpyHostToDevice);
	//cudaMemcpy(host, device, bytes, cudaMemcpyDeviceToHost);
	
	if (!gpu_update) {
		return false;
	}

	auto erro = cudaMemcpy(cpu_matrix, gpu_matrix, sizeof(double) * sz, cudaMemcpyDeviceToHost);
	if (erro)
		Error: std::cerr << "Error on CUDA: " << cudaGetErrorString(erro);

	cpu_update = false;
	gpu_update = false;

	cudaDeviceSynchronize();
	return true;
}

bool Matrix::updateGPU() const
{
	if (!cpu_update) {
		return false;
	}
	//cudaMemcpy(device, host, bytes, cudaMemcpyHostToDevice);
	//cudaMemcpy(host, device, bytes, cudaMemcpyDeviceToHost);

	auto erro =	cudaMemcpy(gpu_matrix, cpu_matrix, sizeof(double) * sz, cudaMemcpyHostToDevice);
	if (erro)
	Error: std::cerr << "Error on CUDA: " << cudaGetErrorString(erro);

	cpu_update = false;
	gpu_update = false;

	cudaDeviceSynchronize();
	return true;
}



void Matrix::assert_cpu_update(bool update)
{
	cpu_update = update;
}

void Matrix::assert_gpu_update(bool update)
{
	gpu_update = true;
}

void Matrix::force_cpu_update()
{
	gpu_update = true; 
	updateCPU();
}

void Matrix::force_gpu_update()
{
	cpu_update = true;
	updateGPU();
}

Matrix::Matrix(unsigned int length, unsigned int width)
{
	x_dim = length;
	y_dim = width;
	sz = x_dim * y_dim;

	initialize();
}

Matrix::Matrix(std::vector<double> m, int x, int y)
{
	x_dim = x;
	y_dim = y;
	sz = x * y;

	initialize();

	for (int i = 0; i < m.size(); ++i) {
		(*this)[i] = m[i];
	}
	cpu_update = true;
	updateGPU();
}

Matrix::Matrix(const Matrix & cpy)
{
	if (cpy.cpu_update) {
		cpy.updateGPU();
	}

	x_dim = cpy.x_dim;
	y_dim = cpy.y_dim;
	sz = cpy.sz;

	initialize();
	copy <<<n_blocks, n_threads >> > (gpu_matrix, cpy.gpu_matrix, sz);
	gpu_update = true;
}

Matrix::Matrix()
{
	x_dim = -1;
	y_dim = -1;
	sz = -1;
	initialized = false;
}

Matrix::~Matrix()
{
	cudaFree(gpu_matrix);
	delete[] cpu_matrix;
}

int Matrix::length() const
{
	return x_dim;
}

int Matrix::width() const
{
	return y_dim;
}

int Matrix::size() const
{
	return sz;
}

void Matrix::print()
{
	//std::cout << " print method does not support transposed print " << std::endl;
	updateCPU();
		//std::cout << " not " << std::endl;
		for (int i = 0; i < sz; ++i) {
			if (i % x_dim == 0) {
				std::cout << std::endl;
			}
			std::cout << cpu_matrix[i] << " ";
		}
	std::cout << std::endl;
}


void Matrix::print(int p)
{
	std::cout.precision(p);
	print();
}
double & Matrix::operator[](int i)
{
	updateCPU();
	cpu_update = true;
	return cpu_matrix[i];
}

double & Matrix::operator()(int x, int y)
{
	//std::cout << " () oper method does not support transpose " << std::endl;

	updateCPU();
	cpu_update = true;
	return cpu_matrix[y * length() + x];
}

Matrix & Matrix::operator=(const Matrix & m)
{
	chkBounds(m);
	updateGPU();
	gpu_update = true;

	if (length() != m.length() || width() != m.width()) {
		throw std::invalid_argument("length/width mismatch");
	}

	copy<<<n_blocks, n_threads>>>(gpu_matrix, m.gpu_matrix, sz);
	cudaDeviceSynchronize();
	return *this;
}

Matrix Matrix::T()
{
	return transpose();
}

Matrix Matrix::transpose() const
{
	//does not work
	Matrix r = Matrix(width(), length());

	Matrices_gpu::transpose << <n_blocks, n_threads >> >(r.gpu_matrix, gpu_matrix, length(), width());
	cudaDeviceSynchronize();
	r.gpu_update = true;

	return r;
}

void Matrix::fill(double v)
{
	gpu_update = true;
	Matrices_gpu::fill <<<n_blocks, n_threads >>>(gpu_matrix, v, sz);
	cudaDeviceSynchronize();
}

Matrix Matrix::operator^(const Matrix & m) const
{
	chkBounds(m);

	updateGPU();
	m.updateGPU();

	Matrix r = Matrix(x_dim, y_dim);
	exp << <n_blocks, n_threads >> > (r.gpu_matrix, gpu_matrix, m.gpu_matrix, sz);
	cudaDeviceSynchronize();

	r.gpu_update = true;
	return r;
}

Matrix Matrix::operator*(const Matrix & m) const
{
	//Yeah this code sucks -- will try to make it pretty later 

	updateGPU();
	m.updateGPU();

	chkBounds_dotProduct(m);
	Matrix r = Matrix(width(), m.length());

	int n_blocks = 256; //arbitrary init
	int n_threads = 32; //arbitrary init
	int n_computations = length() * width() * m.width();

	//If there are only 1 set of threads 
	if (n_computations < 32) {
		n_blocks = 1;
		n_threads = 1;
	}
	else {
		n_blocks = ceil(n_computations / 32);
		n_threads = ceil(n_computations / n_blocks);

		if (n_blocks > MAX_BLOCK_dimx) {
			n_blocks = MAX_BLOCK_dimx;
	
			n_threads = ceil(n_computations / n_blocks);
			if (n_threads > MAX_THREADS) {
				n_threads = MAX_THREADS;
			}
		}
	}

	dot << <n_blocks, n_threads >> > (r.gpu_matrix, gpu_matrix, length(), width(), m.gpu_matrix, m.length(), m.width());
	cudaDeviceSynchronize();

	r.gpu_update = true;
	return r;
}
Matrix Matrix::operator->*(const Matrix & m) const
{
	//Yeah this code sucks -- will try to make it pretty later 

	updateGPU();
	m.updateGPU();

	chkBounds_dotProduct_transposed(m);
	Matrix r = Matrix(width(), m.length());

	int n_blocks = 256; //arbitrary init
	int n_threads = 32; //arbitrary init
	int n_computations = length() * width() * m.width();

	//If there are only 1 set of threads 
	if (n_computations < 32) {
		n_blocks = 1;
		n_threads = 1;
	}
	else {
		n_blocks = ceil(n_computations / 32);
		n_threads = ceil(n_computations / n_blocks);

		if (n_blocks > MAX_BLOCK_dimx) {
			n_blocks = MAX_BLOCK_dimx;

			n_threads = ceil(n_computations / n_blocks);
			if (n_threads > MAX_THREADS) {
				n_threads = MAX_THREADS;
			}
		}
	}
	dot_transpose<< <n_blocks, n_threads >> > (r.gpu_matrix, gpu_matrix, x_dim, y_dim, m.gpu_matrix, m.length(), m.width());
	cudaDeviceSynchronize();

	r.gpu_update = true;
	return r;
}
//LENGTH WIDTH X_DIM Y_DIM NOT UPDATED BELOW HERE
Matrix Matrix::operator&(const Matrix & m) const
{
	updateGPU();
	m.updateGPU(); 

	chkBounds(m);
	Matrix r = Matrix(length() , width());
	multiply << <n_blocks, n_threads >> > (r.gpu_matrix, gpu_matrix, m.gpu_matrix, sz);
	cudaDeviceSynchronize();

	r.gpu_update = true;

	return r;
}

Matrix Matrix::operator/(const Matrix & m) const
{
	updateGPU();
	m.updateGPU();

	chkBounds(m);
	Matrix r = Matrix(length(), width());
	divide << <n_blocks, n_threads >> > (r.gpu_matrix, gpu_matrix, m.gpu_matrix, sz);
	cudaDeviceSynchronize();

	r.gpu_update = true;

	return r;
}

Matrix Matrix::operator+(const Matrix & m) const
{
	updateGPU();
	m.updateGPU();

	chkBounds(m);
	Matrix r = Matrix(length(), width());
	add << <n_blocks, n_threads >> > (r.gpu_matrix, gpu_matrix, m.gpu_matrix, sz);
	cudaDeviceSynchronize();

	r.gpu_update = true;

	return r;
}

Matrix Matrix::operator-(const Matrix & m) const
{
	updateGPU();
	m.updateGPU();

	chkBounds(m);
	Matrix r = Matrix(length(), width());
	subtract << <n_blocks, n_threads >> > (r.gpu_matrix, gpu_matrix, m.gpu_matrix, sz);
	cudaDeviceSynchronize();

	r.gpu_update = true;

	return r;
}

Matrix& Matrix::operator^=(const Matrix & m)
{
	updateGPU();
	m.updateGPU();
	gpu_update = true;

	chkBounds(m);
	exp << <n_blocks, n_threads >> > (gpu_matrix, gpu_matrix, m.gpu_matrix, sz);
	cudaDeviceSynchronize();

	return *this;
}

Matrix & Matrix::operator&=(const Matrix & m)
{
	chkBounds(m);
	updateGPU();
	m.updateGPU();
	gpu_update = true;

	multiply << <n_blocks, n_threads >> > (gpu_matrix, gpu_matrix, m.gpu_matrix, sz);
	cudaDeviceSynchronize();
	return *this;
}

Matrix & Matrix::operator/=(const Matrix & m)
{
	chkBounds(m);
	updateGPU();
	m.updateGPU();
	gpu_update = true;

	divide << <n_blocks, n_threads >> > (gpu_matrix, gpu_matrix, m.gpu_matrix, sz);
	cudaDeviceSynchronize();
	return *this;
}

Matrix & Matrix::operator+=(const Matrix & m)
{
	chkBounds(m);
	updateGPU();
	m.updateGPU();
	gpu_update = true;

	add << <256, 256 >> >(gpu_matrix, gpu_matrix, m.gpu_matrix, sz);
	cudaDeviceSynchronize();
	return *this;
}

Matrix & Matrix::operator-=(const Matrix & m)
{
	chkBounds(m);
	updateGPU();
	m.updateGPU();
	gpu_update = true;

	subtract << <n_blocks, n_threads >> >(gpu_matrix, gpu_matrix, m.gpu_matrix, sz);
	cudaDeviceSynchronize();
	return *this;
}

Matrix Matrix::operator^(double v) const
{
	updateGPU();

	Matrix r = Matrix(length(), width());
	exp << <n_blocks, n_threads >> >(r.gpu_matrix, gpu_matrix, v, sz);
	cudaDeviceSynchronize();

	r.gpu_update = true;
	return r;
}

Matrix Matrix::operator/(double v) const
{
	updateGPU();

	Matrix r = Matrix(length(), width());
	divide << <n_blocks, n_threads >> >(r.gpu_matrix, gpu_matrix, v, sz);
	cudaDeviceSynchronize();

	r.gpu_update = true;
	return r;
}

Matrix Matrix::operator+(double v) const
{
	updateGPU();

	Matrix r = Matrix(length(), width());
	add << <n_blocks, n_threads >> >(r.gpu_matrix, gpu_matrix, v, sz);
	cudaDeviceSynchronize();
	
	r.gpu_update = true;
	return r;
}

Matrix Matrix::operator-(double v) const
{
	updateGPU();

	Matrix r = Matrix(length(), width());
	subtract << <n_blocks, n_threads >> >(r.gpu_matrix, gpu_matrix, v, sz);
	cudaDeviceSynchronize();

	r.gpu_update = true;
	return r;
}

Matrix Matrix::operator&(double v) const
{
	updateGPU();

	Matrix r = Matrix(length(), width());
	multiply << <n_blocks, n_threads >> >(r.gpu_matrix, gpu_matrix, v, sz);
	cudaDeviceSynchronize();

	r.gpu_update = true;
	return r;
}

Matrix & Matrix::operator^=(double v)
{
	updateGPU();
	gpu_update = true;

	exp << <n_blocks, n_threads >> >(gpu_matrix, gpu_matrix, v, sz);
	cudaDeviceSynchronize();

	return *this;
}

Matrix & Matrix::operator/=(double v)
{
	updateGPU();
	gpu_update = true;

	divide << <n_blocks, n_threads >> >(gpu_matrix, gpu_matrix, v, sz);
	cudaDeviceSynchronize();

	return *this;
}

Matrix & Matrix::operator+=(double v)
{
	updateGPU();
	gpu_update = true;

	add << <n_blocks, n_threads >> >(gpu_matrix, gpu_matrix, v, sz);
	cudaDeviceSynchronize();

	return *this;
}

Matrix & Matrix::operator-=(double v)
{
	updateGPU();
	gpu_update = true;

	subtract << <n_blocks, n_threads >> >(gpu_matrix, gpu_matrix, v, sz);
	cudaDeviceSynchronize();

	return *this;
}

Matrix & Matrix::operator&=(double v)
{
	updateGPU();
	gpu_update = true;

	multiply << <n_blocks, n_threads >> >(gpu_matrix, gpu_matrix, v, sz);
	cudaDeviceSynchronize();

	return *this;
}

void Matrix::chkBounds(const Matrix & m) const
{
	if (length() != m.length()) {
		std::cout << "chkBounds fail *this.length() [" <<
			length() << "] != param.length() [" << m.length() << "]" << std::endl;
		throw std::invalid_argument("err");
	}
	else if (width() != m.width()) {
		std::cout << "chkBounds fail *this.width() [" <<
			width() << "] != param.width() [" << m.width() << "]" << std::endl;
		throw std::invalid_argument("err");
	}
}
void Matrix::chkBounds_dotProduct(const Matrix & m) const
{
	if (width() != m.length()) {
		std::cout << "chkBounds dotProduct fail this.width() = " << width() << " param.m.width() == " << m.width() << std::endl;
		throw std::invalid_argument("error");
	}
}

void Matrix::chkBounds_dotProduct_transposed(const Matrix & m) const
{
	if (length() != m.length()) {
		std::cout << "chkBounds dotProduct.T() fail this.length() = " << length() << " param.m.length() == " << m.length() << std::endl;
		throw std::invalid_argument("error");
	}
}
void Matrix::chkBounds_dot_dimensions(const Matrix & m1, const Matrix & m2) const
{
	m1.chkBounds_dotProduct(m2);
	if (length() != m1.length() || width() != m2.width()) {
		std::cout << "chkBounds dot product set dimensions invalid " << std::endl;
		throw std::invalid_argument("error");

	}
}
void Matrix::chkBounds(const Matrix & m, std::string message) const
{
	if (length() != m.length()) {
		std::cout << &message << std::endl;
		std::cout << "chkBounds fail *this.length() [" <<
			length() << "] != param.length() [" << m.length() << "]" << std::endl;
		throw std::invalid_argument("err");
	}
	else if (width() != m.width()) {
		std::cout << &message << std::endl;
		std::cout << "chkBounds fail *this.width() [" <<
			width() << "] != param.width() [" << m.width() << "]" << std::endl;
		throw std::invalid_argument("err");
	}
}
void Matrix::chkBounds_dotProduct(const Matrix & m, std::string message) const
{
	if (width() != m.length()) {
		std::cout << &message << std::endl;
		std::cout << "chkBounds dotProduct fail this.width() = " << width() << " param.m.width() == " << m.width() << std::endl;
		throw std::invalid_argument("error");
	}
}
void Matrix::chkBounds_dot_dimensions(const Matrix & m1, const Matrix & m2, std::string message) const
{
	m1.chkBounds_dotProduct(m2);
	if (length() != m1.length() || width() != m2.width()) {
		std::cout << &message << std::endl;
		std::cout << "chkBounds dot product set dimensions invalid " << std::endl;
		throw std::invalid_argument("error");
	}
}

