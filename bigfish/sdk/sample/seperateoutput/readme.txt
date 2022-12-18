Purpose: to demonstrate the SeperateOutput  scenario.
Command: SeperateOutput freq [srate] [qamtype or polarization] [hd_vo_format]
      Fields [srate], [qamtype or polarization] and [hd_vo_format] are optional.
      srate:
          For cable, default 6875
          For satellite, default 27500
      qamtype or polarization:
          For cable, used as qamtype, value can be 16|32|[64]|128|256|512 defaut[64]
          For satellite, used as polarization, value can be [0] horizontal | 1 vertical defaut[0]
      hd_vo_format:
          The value of vo_format can be 1080P_60, 1080P_50, 1080i_60, 1080i_50, 720P_60, or 720P_50. The default value is 
          1080i_50.