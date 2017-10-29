# FiSSH
SSH authentication via Fingerprint scanning over network (SSL Sockets).

# How does it work?
The android app remembers your SSH key phrase and sends it to your PC when an authorized fingerprint is detected. The PC app then returns the received passphrase to OpenSSH and the standard ssh binary completes the login process.

It is important to note that none of the FiSSH apps had access to private key file, which ensures the security of FiSSH! 

# How to install?
Please see INSTALL.md

# Credits
Fingerprint icon created by Freepik (https://www.freepik.com)
