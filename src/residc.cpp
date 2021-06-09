#include "../deps/sid.h"
#include "../deps/siddefs.h"

#include "residc.h"

extern "C"
{
	SidHandle* SID_create(void)
	{
		return CAST(SidHandle, new SID());
	}

	void SID_destroy(SidHandle* handle)
	{
		delete SIDCAST;
	}

	void SID_reset(SidHandle* handle)
	{
		SIDCAST->reset();
	}

	void SID_input(SidHandle* handle, int sample)
	{
		SIDCAST->input(sample);
	}

	int SID_output(SidHandle* handle)
	{
		return SIDCAST->output();
	}

	int SID_output_bits(SidHandle* handle, int bits)
	{
		return SIDCAST->output(bits);
	}

	void SID_set_chip_model(SidHandle* handle, SID_ChipModel model)
	{
		SIDCAST->set_chip_model(model);
	}

	void SID_enable_filter(SidHandle* handle, int enable)
	{
		SIDCAST->enable_filter(enable != 0);
	}

	void SID_enable_external_filter(SidHandle* handle, int enable)
	{
		SIDCAST->enable_external_filter(enable != 0);
	}

	int SID_set_sampling_parameters(SidHandle* handle, double clock_freq, SID_SamplingMethod sampling_method,
		double sample_freq, double pass_freq, double filter_scale)
	{
		return SIDCAST->set_sampling_parameters(clock_freq, sampling_method, sample_freq, pass_freq, filter_scale);
	}

	SID_Reg8 SID_read(SidHandle* handle, SID_Reg8 offset)
	{
		return SIDCAST->read(offset);
	}

	void SID_write(SidHandle* handle, SID_Reg8 offset, SID_Reg8 value)
	{
		return SIDCAST->write(offset, value);
	}

	void SID_read_state(SidHandle* handle, SID_State* out_state)
	{
		SID_State ret_state = { 0 };
		SID::State state = SIDCAST->read_state();

		COPY_STATE(state.sid_register, ret_state.sid_register, 0x20);

		ret_state.bus_value = state.bus_value;
		ret_state.bus_value_ttl = state.bus_value_ttl;

		COPY_STATE(state.accumulator, ret_state.accumulator, 3);
		COPY_STATE(state.shift_register, ret_state.shift_register, 3);
		COPY_STATE(state.rate_counter, ret_state.rate_counter, 3);
		COPY_STATE(state.rate_counter_period, ret_state.rate_counter_period, 3);
		COPY_STATE(state.exponential_counter, ret_state.exponential_counter, 3);
		COPY_STATE(state.exponential_counter_period, ret_state.exponential_counter_period, 3);
		COPY_STATE(state.envelope_counter, ret_state.envelope_counter, 3);
		COPY_STATE(state.envelope_state, ret_state.envelope_state, 3);
		COPY_STATE(state.hold_zero, ret_state.hold_zero, 3);

		*out_state = ret_state;
	}

	void SID_write_state(SidHandle* handle, SID_State* in_state)
	{
		SID::State sid_state;
		SID_State state = *in_state;

		COPY_STATE(state.sid_register, sid_state.sid_register, 0x20);

		sid_state.bus_value = state.bus_value;
		sid_state.bus_value_ttl = state.bus_value_ttl;

		COPY_STATE(state.accumulator, sid_state.accumulator, 3);
		COPY_STATE(state.shift_register, sid_state.shift_register, 3);
		COPY_STATE(state.rate_counter, sid_state.rate_counter, 3);
		COPY_STATE(state.rate_counter_period, sid_state.rate_counter_period, 3);
		COPY_STATE(state.exponential_counter, sid_state.exponential_counter, 3);
		COPY_STATE(state.exponential_counter_period, sid_state.exponential_counter_period, 3);
		COPY_STATE(state.envelope_counter, sid_state.envelope_counter, 3);
		COPY_STATE(state.envelope_state, sid_state.envelope_state, 3);
		COPY_STATE(state.hold_zero, sid_state.hold_zero, 3);

		SIDCAST->write_state(sid_state);
	}

	void SID_adjust_sampling_frequency(SidHandle* handle, double sample_freq)
	{
		SIDCAST->adjust_sampling_frequency(sample_freq);
	}

	void SID_clock(SidHandle* handle)
	{
		SIDCAST->clock();
	}

	void SID_clock_delta(SidHandle* handle, SID_CycleCount delta)
	{
		SIDCAST->clock(delta);
	}

	int SID_clock_output(SidHandle* handle, SID_CycleCount delta, short* buf, int n)
	{
		return SIDCAST->clock(delta, buf, n, 1);
	}

	int SID_clock_output_interleave(SidHandle* handle, SID_CycleCount delta, short* buf, int n, int interleave)
	{
		return SIDCAST->clock(delta, buf, n, interleave);
	}
}