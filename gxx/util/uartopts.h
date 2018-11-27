#ifndef GXX_UTIL_UARTOPS_H
#define GXX_UTIL_UARTOPS_H

namespace gxx
{
  namespace serial
  {

    /*!
     * Enumeration defines the possible bytesizes for the serial port.
     */
    typedef enum {
      fivebits = 5,
      sixbits = 6,
      sevenbits = 7,
      eightbits = 8
    } bytesize;

    /*!
     * Enumeration defines the possible parity types for the serial port.
     */
    typedef enum {
      parity_none = 0,
      parity_odd = 1,
      parity_even = 2,
      parity_mark = 3,
      parity_space = 4
    } parity;

    /*!
     * Enumeration defines the possible stopbit types for the serial port.
     */
    typedef enum {
      stopbits_one = 1,
      stopbits_two = 2,
      stopbits_one_point_five
    } stopbits;

    /*!
     * Enumeration defines the possible flowcontrol types for the serial port.
     */
    typedef enum {
      flowcontrol_none = 0,
      flowcontrol_software,
      flowcontrol_hardware
    } flowcontrol;

  }
}

#endif
