cdef extern from "synthizer_constants.h":

    cdef enum SYZ_PANNER_STRATEGIES:
        SYZ_PANNER_STRATEGY_HRTF
        SYZ_PANNER_STRATEGY_STEREO
        SYZ_PANNER_STRATEGY_COUNT

    cdef enum SYZ_DISTANCE_MODEL:
        SYZ_DISTANCE_MODEL_NONE
        SYZ_DISTANCE_MODEL_LINEAR
        SYZ_DISTANCE_MODEL_EXPONENTIAL
        SYZ_DISTANCE_MODEL_INVERSE
        SYZ_DISTANCE_MODEL_COUNT

    cdef enum SYZ_CONTEXT_PROPERTIES:
        SYZ_CONTEXT_LISTENER_POSITION
        SYZ_CONTEXT_LISTENER_ORIENTATION
        SYZ_CONTEXT_DISTANCE_MODEL
        SYZ_CONTEXT_DISTANCE_REF
        SYZ_CONTEXT_DISTANCE_MAX
        SYZ_CONTEXT_ROLLOFF
        SYZ_CONTEXT_CLOSENESS_BOOST
        SYZ_CONTEXT_CLOSENESS_BOOST_DISTANCE

    cdef enum SYZ_PANNED_SOURCE_PROPERTIES:
        SYZ_PANNED_SOURCE_AZIMUTH
        SYZ_PANNED_SOURCE_ELEVATION
        SYZ_PANNED_SOURCE_PANNING_SCALAR
        SYZ_PANNED_SOURCE_PANNER_STRATEGY
        SYZ_PANNED_SOURCE_GAIN

    cdef enum SYZ_SOURCE3D_PROPERTIES:
        SYZ_SOURCE3D_POSITION
        SYZ_SOURCE3D_ORIENTATION
        SYZ_SOURCE3D_DISTANCE_MODEL
        SYZ_SOURCE3D_DISTANCE_REF
        SYZ_SOURCE3D_DISTANCE_MAX
        SYZ_SOURCE3D_ROLLOFF
        SYZ_SOURCE3D_CLOSENESS_BOOST
        SYZ_SOURCE3D_CLOSENESS_BOOST_DISTANCE
