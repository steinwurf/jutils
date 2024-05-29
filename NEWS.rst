News for jutils
===============

This file lists the major changes between versions. For a more detailed list of
every change, see the Git log.

Latest
------
* Major: Update dependencies and use new waf.

3.1.0
-----
* Minor: Add ``jthrows`` class for exception helpers.
* Minor: Fix ``byte_byffer::set_position`` to also work on older devices.

3.0.1
-----
* Patch: Fix build.

3.0.0
-----
* Major: ``byte_buffer::data`` is now called ``byte_buffer::direct_data``, and
  requires a ByteBuffer which is directly allocated..

2.2.1
-----
* Patch: Fix bug in ``byte_buffer::set_position``.

2.2.0
-----
* Minor: Added ``byte_buffer`` wrapper.

2.1.0
-----
* Minor: Added ``get_boolean``, ``get_byte``, ``get_short``, ``get_int``,
  ``get_long``, ``get_float``, ``get_double``, and ``get_string``.

2.0.0
-----
* Major: Updated CMake integration.

1.1.0
-----
* Minor: Added ``ptr_container``.

1.0.0
-----
* Major: Initial release
