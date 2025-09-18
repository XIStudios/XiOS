#!/bin/bash

# This script runs the 64-bit XiOS kernel in QEMU and serves the
# graphical output directly via a built-in VNC server.

# Use the 64-bit QEMU emulator
QEMU_SYSTEM="qemu-system-x86_64"
OS_IMAGE="build/xios.iso"

# Check if the OS image exists before trying to run it.
if [ ! -f "$OS_IMAGE" ]; then
    echo "Error: ISO image not found at '$OS_IMAGE'."
    echo "Please run ./build.sh first."
    exit 1
fi

echo "Starting QEMU (64-bit) with a built-in VNC server..."

# -cdrom: Tells QEMU to boot from our ISO file.
# -vnc :1:  This is the crucial part. It starts QEMU's own reliable
#           VNC server on the internal port 5901.
# The '&' runs QEMU in the background so this script can continue.
"$QEMU_SYSTEM" -cdrom "$OS_IMAGE" -vnc :1 &
QEMU_PID=$!

# This 'cleanup' function is a safety net. It will run automatically
# when you stop this script (by pressing Ctrl+C).
cleanup() {
    echo "Shutting down QEMU (PID: $QEMU_PID)..."
    kill $QEMU_PID
}
# The 'trap' command registers the cleanup function to run on exit.
trap cleanup EXIT

echo "Starting VNC web proxy..."
echo "Connect to port 6080 in your browser to see the OS."

# This command forwards the public web port (6080) from your Codespace
# to QEMU's internal VNC port (5901).
websockify --web /usr/share/novnc/ 6080 localhost:5901

# The script will wait here until you press Ctrl+C.
# When you do, the 'cleanup' function will automatically run and kill QEMU.