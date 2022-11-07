
  execute_process(
    COMMAND  cmake -E sha256sum C:/Users/Mike/Documents/GitHub/aisRX_pi/build/aisRX-0.5.2.0+2211071232._msvc-6.3.9600-win32.tar.gz
    OUTPUT_FILE C:/Users/Mike/Documents/GitHub/aisRX_pi/build/aisRX-0.5.2.0+2211071232._msvc-6.3.9600-win32.sha256
  )
  file(READ C:/Users/Mike/Documents/GitHub/aisRX_pi/build/aisRX-0.5.2.0+2211071232._msvc-6.3.9600-win32.sha256 _SHA256)
  string(REGEX MATCH "^[^ ]*" checksum ${_SHA256} )
  configure_file(
    C:/Users/Mike/Documents/GitHub/aisRX_pi/build/aisRX-0.5-msvc-6.3.9600.xml.in
    C:/Users/Mike/Documents/GitHub/aisRX_pi/build/aisRX-0.5-msvc-6.3.9600.xml
    @ONLY
  )
