#ifndef RESIDC_H__
#define RESIDC_H__

#ifndef CR_API
#if defined CR_STATIC
#define CR_API
#elif defined(_WIN32)
#define CR_API __declspec(dllimport)
#else
#define CR_API extern
#endif
#endif

#if defined(_WIN32)
#define CR_APIENTRY __cdecl
#else
#define CR_APIENTRY
#endif

#define CAST(x, y) reinterpret_cast<x*>(y)
#define SIDCAST CAST(SID, handle)
#define COPY_STATE(from, to, count) for(char i = 0; i < count; i++) to[i] = from[i];

typedef enum chip_model SID_ChipModel;
typedef enum sampling_method SID_SamplingMethod;

typedef reg4 SID_Reg4;
typedef reg8 SID_Reg8;
typedef reg12 SID_Reg12;
typedef reg16 SID_Reg16;
typedef reg24 SID_Reg24;

typedef cycle_count SID_CycleCount;
typedef sound_sample SID_SoundSample;
typedef fc_point SID_FcPoint;

typedef EnvelopeGenerator::State SID_EnvelopeGeneratorState;

struct SidHandle;
typedef struct SidHandle SidHandle;

struct SidStateHandle;
typedef struct SidStateHandle SidStateHandle;

typedef struct SID_State {
	char sid_register[0x20];
	
	SID_Reg8 bus_value;
	SID_CycleCount bus_value_ttl;

	SID_Reg24 accumulator[3];
	SID_Reg24 shift_register[3];
	SID_Reg16 rate_counter[3];
	SID_Reg16 rate_counter_period[3];
	SID_Reg16 exponential_counter[3];
	SID_Reg16 exponential_counter_period[3];
	SID_Reg8 envelope_counter[3];
	SID_EnvelopeGeneratorState envelope_state[3];
	char hold_zero[3];
} SID_State;

extern "C"
{
	CR_API SidHandle* CR_APIENTRY SID_create();
	CR_API void CR_APIENTRY SID_destroy(SidHandle* handle);

	CR_API void CR_APIENTRY SID_set_chip_model(SidHandle* handle, SID_ChipModel model);
	CR_API void CR_APIENTRY SID_reset(SidHandle* handle);

	CR_API void CR_APIENTRY SID_input(SidHandle* handle, int sample);
	CR_API int CR_APIENTRY SID_output(SidHandle* handle);
	CR_API int CR_APIENTRY SID_output_bits(SidHandle* handle, int bits);

	CR_API SID_Reg8 CR_APIENTRY SID_read(SidHandle* handle, SID_Reg8 offset);
	CR_API void CR_APIENTRY SID_write(SidHandle* handle, SID_Reg8 offset, SID_Reg8 value);

	CR_API void CR_APIENTRY SID_enable_filter(SidHandle* handle, int enable);
	CR_API void CR_APIENTRY SID_enable_external_filter(SidHandle* handle, int enable);

	CR_API int CR_APIENTRY SID_set_sampling_parameters(
		SidHandle* handle, 
		double clock_freq, 
		SID_SamplingMethod sampling_method, 
		double sample_freq, 
		double pass_freq, 
		double filter_scale
	);

	CR_API void CR_APIENTRY SID_read_state(SidHandle* handle, SID_State* state);

	CR_API void CR_APIENTRY SID_adjust_sampling_frequency(SidHandle* handle, double sample_freq);
	CR_API void CR_APIENTRY SID_clock(SidHandle* handle);
	CR_API void CR_APIENTRY SID_clock_delta(SidHandle* handle, SID_CycleCount delta_t);
	CR_API int CR_APIENTRY SID_clock_output(SidHandle* handle, SID_CycleCount delta_t, short* buf, int n);
	CR_API int CR_APIENTRY SID_clock_output_interleave(SidHandle* handle, SID_CycleCount delta_t, short* buf, int n, int interleave);
}

#endif