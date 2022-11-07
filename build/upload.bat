rem
rem  Upload the .tar.gz and .xml artifacts to cloudsmith
rem

echo OFF
if "%CLOUDSMITH_API_KEY%" == "" (
    echo 'Warning: CLOUDSMITH_API_KEY is not available, giving up.'
    echo 'Metadata: aisRX-0.5-msvc-6.3.9600.xml'
    echo 'Tarball: aisRX-0.5.2.0+2211071232._msvc-6.3.9600-win32.tar.gz'
    echo 'Version: 0.5.2.0+2211071232.'
    exit 0
)
echo Using CLOUDSMITH_API_KEY: %CLOUDSMITH_API_KEY:~,4%%...
echo ON

cloudsmith push raw --no-wait-for-sync ^
    --name aisRX-0.5-msvc-6.3.9600-metadata ^
    --version 0.5.2.0+2211071232. ^
    --summary "Plugin metadata for automatic installation" ^
    --republish ^
    mike-rossiter/aisrx-alpha aisRX-0.5-msvc-6.3.9600.xml

cloudsmith push raw --no-wait-for-sync ^
    --name aisRX-0.5-msvc-6.3.9600-tarball ^
    --version 0.5.2.0+2211071232. ^
    --summary "Plugin tarball for automatic installation" ^
    --republish ^
    mike-rossiter/aisrx-alpha aisRX-0.5.2.0+2211071232._msvc-6.3.9600-win32.tar.gz
