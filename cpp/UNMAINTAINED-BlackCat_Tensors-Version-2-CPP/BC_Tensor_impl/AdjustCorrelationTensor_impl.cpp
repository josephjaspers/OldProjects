namespace adjusted {

	template<typename number_type>
	void axpy(number_type* store, const unsigned* store_ld, const number_type* signal, const unsigned* signal_ld, const unsigned* signal_ranks, unsigned signal_order, number_type scalar) {

		--signal_order;

		if (signal_order == 0) {
			for (unsigned i = 0; i < signal_ranks[0]; ++i) {
				//modified axpy
				if (scalar > 1) {
					scalar = 1;
				} else if (scalar < -1) {
					scalar = -1;
				}

				if (scalar < 0)
					store[i] += scalar * signal[i];
				else if (scalar > 0) {
					store[i] += (1 - (scalar * signal[i]));
				}
			}
		} else {

			unsigned store_id = 0;
			unsigned sig_id = 0;
			for (unsigned i = 0; i < signal_ranks[signal_order]; ++i) {
				axpy(&store[store_id], store_ld, &signal[sig_id], signal_ld, signal_ranks, signal_order, scalar);
				store_id += store_ld[signal_order];
				sig_id += signal_ld[signal_order];

			}
		}
	}

	template<typename number_type>
	void adj_cc_filter_error(unsigned move_dimensions, number_type* store, const unsigned* store_ld, const unsigned* store_ranks, unsigned store_order, const number_type* error, const unsigned* error_ld, const unsigned* error_ranks, unsigned error_order, const number_type* signal, const unsigned* signal_ld, const unsigned* signal_ranks, unsigned signal_order) {

		if (move_dimensions > 0) {
			--move_dimensions;

			unsigned move_positions = signal_ranks[move_dimensions] - store_ranks[move_dimensions] + 1;
			unsigned sig_id = 0;
			unsigned err_id = 0;

			unsigned signal_base_index = 1;
			unsigned error_base_index = 1;

			for (int i = move_dimensions; i > 0; --i) {
				error_base_index *= error_ld[i];
				signal_base_index *= signal_ld[i];
			}

			for (unsigned i = 0; i < move_positions; ++i) {
				adj_cc_filter_error(move_dimensions, store, store_ld, store_ranks, store_order, &error[err_id], error_ld, error_ranks, error_order,
						&signal[sig_id], signal_ld, signal_ranks, signal_order);
				sig_id += signal_base_index;
				err_id += error_base_index;
			}
		} else {
			axpy(store, store_ld, signal, signal_ld, store_ranks, signal_order, *error);
		}
	}

	template<typename number_type>
	void adj_cc_signal_error(unsigned move_dimensions, number_type* store, const unsigned* store_ld, const unsigned* store_ranks, unsigned store_order, const number_type* error, const unsigned* error_ld, const unsigned* error_ranks, unsigned error_order, const number_type* filter, const unsigned* filter_ld, const unsigned* filter_ranks, unsigned filter_order) {

		if (move_dimensions > 0) {
			--move_dimensions;

			unsigned move_positions = move_dimensions < error_order ? error_ranks[move_dimensions] : 1;
			unsigned err_id = 0;
			unsigned sto_id = 0;

			//		unsigned store_base_index = 1;
			//		unsigned error_base_index = 1;
			//
			//		for (int i = move_dimensions; i > 0; --i) {
			//			error_base_index *= error_ld[i];
			//			store_base_index *= store_ld[i];
			//		}

			for (unsigned i = 0; i < move_positions; ++i) {
				adj_cc_signal_error(move_dimensions, &store[sto_id], store_ld, store_ranks, store_order, &error[err_id], error_ld, error_ranks,
						error_order, filter, filter_ld, filter_ranks, filter_order);
				err_id += error_ld[move_dimensions];
				sto_id += store_ld[move_dimensions];
			}
		} else {
			axpy(store, store_ld, filter, filter_ld, filter_ranks, filter_order, *error);
		}
	}

	template<typename number_type>
	void correlation(number_type* s, const number_type* filter, const number_type* signal, unsigned sz) {
		number_type tmp = 0;
		for (unsigned i = 0; i < sz; ++i) {
			tmp += filter[i] - signal[i];
		}
		*s = tmp;
	}

	template<typename number_type>
	void ADJUSTED_correlation(number_type* s, unsigned order, const unsigned* ranks, const number_type* filter, const unsigned* f_ld, const number_type* signal, const unsigned* s_ld) {
		//WORKS
		--order;
		if (order == 0) {
			number_type tmp = 0;
			adjusted::correlation(&tmp, filter, signal, ranks[0]);
			*s += tmp;
		} else {

			for (unsigned i = 0; i < ranks[order]; ++i) {
				adjusted::ADJUSTED_correlation(s, order, ranks, &filter[i * f_ld[order]], f_ld, &signal[i * s_ld[order]], s_ld);
			}
		}
	}

	template<typename number_type>
	void ADJUSTED_cross_correlation(number_type* s, unsigned cor_mv, const unsigned* store_ld, const number_type* filter, const unsigned * f_ld, const unsigned* f_ranks, unsigned f_order, const number_type* signal, const unsigned * s_ld, const unsigned* s_ranks, unsigned s_order) {
		if (cor_mv == 0) {
			adjusted::ADJUSTED_correlation(s, f_order, f_ranks, filter, f_ld, signal, s_ld);
		}

		else if (s_order > f_order) {
			--s_order;

			unsigned s_id = 0;
			for (unsigned i = 0; i < s_ranks[s_order]; ++i) {
				adjusted::ADJUSTED_cross_correlation(s, cor_mv, store_ld, filter, f_ld, f_ranks, f_order, &signal[s_id], s_ld, s_ranks, s_order);

				s_id += s_ld[s_order];
			}
		}

		else {
			--cor_mv;

			unsigned store_id = 0;
			unsigned s_id = 0;

			unsigned mv_positions = s_ranks[cor_mv] + 1;
			mv_positions -= f_order < cor_mv + 1 ? 1 : f_ranks[cor_mv];

			for (unsigned i = 0; i < mv_positions; ++i) {
				adjusted::ADJUSTED_cross_correlation(&s[store_id], cor_mv, store_ld, filter, f_ld, f_ranks, f_order, &signal[s_id], s_ld, s_ranks,
						s_order);

				store_id += store_ld[cor_mv];
				s_id += s_ld[cor_mv];
			}
		}
	}

	template<typename number_type>
	void abs(number_type* data, unsigned sz) {
		for (int i = 0; i < sz; ++i) {
			if (data[i] < 0) {
				data[i] *= -1;
			}
		}
	}

}
;

#include "Tensor.h"
#include "BLACKCAT_EXPLICIT_INSTANTIATION.h"

template<typename number_type, class TensorOperations>
Tensor<number_type, TensorOperations> Tensor<number_type, TensorOperations>::ADJUSTED_x_corr_stack(unsigned dims, const Tensor<number_type,
		TensorOperations>& t) const {

	Shape x_shape(dims + 1);
	for (unsigned i = 0; i < dims; ++i) {
		if (i < order - 1)
			x_shape[i] = t.rank(i) - rank(i) + 1;
		else {
			x_shape[i] = t.rank(i);
		}
	}

	x_shape.back() = outerRank();
	Tensor<number_type, TensorOperations> output(x_shape);
	output.zeros();

	for (unsigned i = 0; i < output.outerRank(); ++i) {
		adjusted::ADJUSTED_cross_correlation(&output.tensor[i * output.outerLD()], dims, output.ld, &tensor[i * ld[order - 1]], ld, ranks, order - 1,
				t.tensor, t.ld, t.ranks, t.order);
	}

	Tensor<number_type, TensorOperations> adjusted_output(x_shape);
	adjusted_output.zeros();
	unsigned krnl_sz = (this->sz / this->outerRank());
	adjusted::abs(output.data(), output.size());

	//adjusted_output -= (output /= krnl_sz);
	//output.print();

	adjusted_output += (output / krnl_sz);

	return adjusted_output;
}

template<typename number_type, class TensorOperations> //valid x_corr
Tensor<number_type, TensorOperations> Tensor<number_type, TensorOperations>::ADJUSTED_x_corr_FilterError(unsigned move_dimensions, const Tensor<
		number_type, TensorOperations>& error) const {

	//this = the signal  t is the error
	Shape original_filter_shape(this->degree()); //same dimensions
	for (unsigned i = 0; i < degree(); ++i) {
		if (i < move_dimensions)
			original_filter_shape[i] = this->ranks[i] - error.ranks[i] + 1;
		else
			original_filter_shape[i] = this->ranks[i];
	}
	Tensor<number_type, TensorOperations> output(original_filter_shape);
	output.zeros();
	adjusted::adj_cc_filter_error(move_dimensions, output.tensor, output.ld, output.ranks, output.order, error.tensor, error.ld, error.ranks,
			error.order, tensor, ld, ranks, order);
	return output;
}

template<typename number_type, class TensorOperations> //valid x_corr
Tensor<number_type, TensorOperations> Tensor<number_type, TensorOperations>::AdJUSTED_x_corr_SignalError(unsigned move_dimensions, const Tensor<
		number_type, TensorOperations>& error) const {

	//this = the weights  t is the error
	Shape original_filter_shape(this->degree()); //same dimensions
	for (unsigned i = 0; i < degree(); ++i) {
		if (i < move_dimensions)
			original_filter_shape[i] = this->rank(i) + error.rank(i) - 1;
		else
			original_filter_shape[i] = this->rank(i);
	}
	Tensor<number_type, TensorOperations> output(original_filter_shape);
	output.zeros();

	adjusted::adj_cc_signal_error(move_dimensions, output.tensor, output.ld, output.ranks, output.order, error.tensor, error.ld, error.ranks,
			error.order, tensor, ld, ranks, order);
	return output;
}
