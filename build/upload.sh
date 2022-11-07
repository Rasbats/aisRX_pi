#!/usr/bin/env bash

#
# Upload the .tar.gz and .xml artifacts to cloudsmith
#

if [ -f ~/.config/local-build.rc ]; then source ~/.config/local-build.rc; fi

if [ -z "$CLOUDSMITH_API_KEY" ]; then
    echo 'Warning: $CLOUDSMITH_API_KEY is not available, giving up.'
    echo 'Metadata: aisRX-0.5-msvc-6.3.9600.xml'
    echo 'Tarball: aisRX-0.5.2.0+2211071232._msvc-6.3.9600-win32.tar.gz'
    echo 'Version: 0.5.2.0+2211071232.'
    exit 0
fi

echo "Using CLOUDSMITH_API_KEY: ${CLOUDSMITH_API_KEY:0:4}..."

if [ -f ~/.uploadrc ]; then source ~/.uploadrc; fi
set -xe

cloudsmith push raw --no-wait-for-sync \
    --name aisRX-0.5-msvc-6.3.9600-metadata \
    --version 0.5.2.0+2211071232. \
    --summary "Plugin metadata for automatic installation" \
    --republish \
    mike-rossiter/aisrx-alpha aisRX-0.5-msvc-6.3.9600.xml

cloudsmith push raw --no-wait-for-sync \
    --name aisRX-0.5-msvc-6.3.9600-tarball \
    --version 0.5.2.0+2211071232. \
    --summary "Plugin tarball for automatic installation" \
    --republish \
    mike-rossiter/aisrx-alpha aisRX-0.5.2.0+2211071232._msvc-6.3.9600-win32.tar.gz
