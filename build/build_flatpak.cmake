
    execute_process(
      COMMAND
        flatpak-builder --force-clean --keep-build-dirs
          C:/Users/Mike/Documents/GitHub/aisRX_pi/build/app C:/Users/Mike/Documents/GitHub/aisRX_pi/flatpak/org.opencpn.OpenCPN.Plugin.aisRX.yaml
    )
    # Copy the data out of the sandbox to installation directory
    execute_process(
      COMMAND
        flatpak-builder  --run app C:/Users/Mike/Documents/GitHub/aisRX_pi/flatpak/org.opencpn.OpenCPN.Plugin.aisRX.yaml  bash -c "
          set -x; stable_link=$(find /run/build -maxdepth 1 -type l);           cp -ar $stable_link/app/files/*                         C:/Users/Mike/Documents/GitHub/aisRX_pi/build/app/files
        "
    )
    execute_process(
      COMMAND bash -c "sed -e '/@checksum@/d'           < aisRX-0.5-msvc-6.3.9600.xml.in > app/files/metadata.xml"
    )
    if ( MATCHES Release|MinSizeRel)
      message(STATUS "Stripping app/files/lib/opencpn/libaisRX_pi.so")
      execute_process(
        COMMAND strip app/files/lib/opencpn/libaisRX_pi.so
      )
    endif ()
    execute_process(
      WORKING_DIRECTORY C:/Users/Mike/Documents/GitHub/aisRX_pi/build/app
      COMMAND mv -fT files aisRX-0.5-msvc-6.3.9600
    )
    execute_process(
      WORKING_DIRECTORY  C:/Users/Mike/Documents/GitHub/aisRX_pi/build/app
      COMMAND
        cmake -E
        tar -czf ../aisRX-0.5.2.0+2211071232._msvc-6.3.9600-win32.tar.gz --format=gnutar aisRX-0.5-msvc-6.3.9600
    )
    message(STATUS "Building aisRX-0.5.2.0+2211071232._msvc-6.3.9600-win32.tar.gz")
    execute_process(
      COMMAND cmake -P C:/Users/Mike/Documents/GitHub/aisRX_pi/build/checksum.cmake
    )
    message(STATUS "Computing checksum in aisRX-0.5-msvc-6.3.9600.xml")
  