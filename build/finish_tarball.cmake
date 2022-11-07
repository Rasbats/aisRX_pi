
    execute_process(
      COMMAND cmake -E rm -rf app/aisRX-0.5-msvc-6.3.9600
    )
     execute_process(
      COMMAND cmake -E rename app/files app/aisRX-0.5-msvc-6.3.9600
    )
    execute_process(
      WORKING_DIRECTORY C:/Users/Mike/Documents/GitHub/aisRX_pi/build/app
      COMMAND
        cmake -E
        tar -czf ../aisRX-0.5.2.0+2211071232._msvc-6.3.9600-win32.tar.gz --format=gnutar aisRX-0.5-msvc-6.3.9600
    )
    message(STATUS "Creating tarball aisRX-0.5.2.0+2211071232._msvc-6.3.9600-win32.tar.gz")

    execute_process(COMMAND cmake -P C:/Users/Mike/Documents/GitHub/aisRX_pi/build/checksum.cmake)
    message(STATUS "Computing checksum in aisRX-0.5-msvc-6.3.9600.xml")
  