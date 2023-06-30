#!/usr/bin/env bash

#
# Upload the .tar.gz and .xml artifacts to cloudsmith
#

if [ -f ~/.config/local-build.rc ]; then source ~/.config/local-build.rc; fi

if [ -z "$CLOUDSMITH_API_KEY" ]; then
    echo 'Warning: $CLOUDSMITH_API_KEY is not available, giving up.'
    echo 'Metadata: aisRX-0.6-msvc-wx32-10.xml'
    echo 'Tarball: aisRX-0.6.0+2306301021.35b53e2_msvc-wx32-10-win32.tar.gz'
    echo 'Version: 0.6.0+2306301021.35b53e2'
    exit 0
fi

echo "Using CLOUDSMITH_API_KEY: ${CLOUDSMITH_API_KEY:0:4}..."

if [ -f ~/.uploadrc ]; then source ~/.uploadrc; fi
set -xe

cloudsmith push raw --no-wait-for-sync \
    --name aisRX-0.6-msvc-wx32-10-metadata \
    --version 0.6.0+2306301021.35b53e2 \
    --summary "Plugin metadata for automatic installation" \
    --republish \
    mike-rossiter/aisrx-alpha aisRX-0.6-msvc-wx32-10.xml

cloudsmith push raw --no-wait-for-sync \
    --name aisRX-0.6-msvc-wx32-10-tarball \
    --version 0.6.0+2306301021.35b53e2 \
    --summary "Plugin tarball for automatic installation" \
    --republish \
    mike-rossiter/aisrx-alpha aisRX-0.6.0+2306301021.35b53e2_msvc-wx32-10-win32.tar.gz
