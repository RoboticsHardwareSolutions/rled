# RLED Driver Improvement Plan

## API Enhancements (Completed)

- [x] **Unified hardware driver pattern**
  - All drivers (GPIO, PWM, RGB, WS2812) now use config-based interface
  - Config structs include all device state (no separate device struct needed)
  - Status: COMPLETED - Single public header `#include "rled.h"` provides all config types

## P0 - Critical (Breaks Functionality)

- [x] **Static WS2812 device limits multi-instance support**
  - Only one WS2812 strip can exist globally; multiple strips overwrite state
  - Solution: Remove separate device struct, merge into unified config
  - Files: rled.h, rled.c, rled_ws2812.h, rled_ws2812.c
  - **Status**: FIXED - Removed rled_ws2812_device_t, extended rled_ws2812_config_t with device fields (one_frame, zero_frame, reset_delay_us). Now all drivers use config-based pattern.

- [x] **No error handling / return codes**
  - All functions return void; can't detect failures or invalid states
  - Solution: Change all public APIs to return `int` error code
  - Error codes: 0=success, -1=null pointer, -2=invalid type, -3=init failed, -4=invalid param
  - Files: rled.h, rled.c, rled_gpio.c, rled_pwm.c, rled_rgb.c, rled_ws2812.c
  - **Status**: FIXED - Added rled_error_t enum and return codes to all functions

## P1 - High (Functionality Bugs)

- [ ] **PWM period hardcoded to 255**
  - Brightness scaling assumes period=255 but timer may differ
  - Solution: Store actual period in rled_pwm_config_t, scale: `compare = (brightness * period) / 255`
  - Files: rled_pwm.h, rled_pwm.c

- [ ] **Missing null pointer validation in public API**
  - rled_init, rled_on, etc. don't check led pointer
  - Solution: Add `if (!led) return ERROR_NULL_POINTER;` at function start
  - Files: rled.c

- [ ] **WS2812 buffer bounds not validated at encode time**
  - Buffer pointer arithmetic in rled_ws2812_set_led can overflow
  - Solution: Validate `(led_index + 1) * 24 <= buffer_size` before encoding
  - Files: rled_ws2812.c

## P2 - Medium (Code Quality / Documentation)

- [ ] **GPIO init is a no-op**
  - Assumes GPIO pre-configured elsewhere; could fail silently
  - Solution: Either configure GPIO mode or assert with error code
  - Files: rled_gpio.c

- [ ] **Incomplete toggle implementation**
  - Only GPIO supports toggle; PWM/RGB/WS2812 silently do nothing
  - Solution: Document that toggle is GPIO-only or implement for all types
  - Files: rled.c, rled.h

- [ ] **WS2812 SPI timing constants undocumented**
  - WS2812_ONE_FRAME/ZERO_FRAME assume 4 MHz but no validation
  - Solution: Document required SPI frequency and protocol timing
  - Files: rled_ws2812.c (comments)

- [ ] **Unclear buffer lifecycle for WS2812**
  - External buffer ownership not documented (who allocates/frees?)
  - Solution: Add comments in header explaining buffer management
  - Files: rled_ws2812.h

- [ ] **Unvalidated pointer casts**
  - config union void pointers cast without type checking
  - Solution: Add runtime validation or typed accessors
  - Files: rled.c

## Testing Needed

- [ ] Multi-instance WS2812 test (after P0 fix)
- [ ] Error code propagation test
- [ ] PWM brightness scaling with different periods
- [ ] Buffer overflow protection for WS2812
