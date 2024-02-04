# To-do list - Set up de l'environnement de test

# Charge Your MacBook Pro

# Check for and install macOS updates (Note: This may require manual intervention)
softwareupdate -ia

# Update installed applications from the App Store
mas upgrade

# Disable automatic macOS software updates
sudo softwareupdate --schedule off

# Turn off Wi-Fi (Replace en0 with your actual Wi-Fi interface, if different)
sudo ifconfig en0 down

# To disable Ethernet (Replace en1 with your actual Ethernet interface, if different)
sudo ifconfig en1 down

# Close Non-Essential Applications
# Note: Use top or ps to identify running processes and kill to terminate them. Be cautious to only close applications and processes that are safe to terminate.

# Prevent the display from going to sleep
sudo pmset displaysleep 0

# Disable system sleep
sudo pmset sleep 0

# Disable Power Nap
sudo pmset -a powernap 0
Disable Sleep Mode

# Set computer sleep to Never
sudo systemsetup -setcomputersleep Never
Re-enable Networking (Post-Benchmark)

# Turn on Wi-Fi
sudo ifconfig en0 up

# To enable Ethernet
sudo ifconfig en1 up

# Enable automatic macOS software updates
sudo softwareupdate --schedule on

# Restore energy settings to default or as desired
sudo pmset restoredefaults

# Enable system sleep as desired
sudo systemsetup -setcomputersleep 30
