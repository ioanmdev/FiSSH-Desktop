# System Requirements
* Linux
* QT Creator (optional)
* setsid
* OpenSSH/LibreSSH/Something-SSH (just needs to have the "ssh" binary)
configured to use a KEY protected with a PASSPHRASE (which you will have to enter into the Android app!)
* Static LAN ip on your computer (look at /etc/network/interfaces)

# Installing

## On Arch Linux
- Step 1
Download the "fissh" package from AUR (https://aur.archlinux.org/packages/fissh/). "makepkg" and install it.

- Step 2
Add your user to the "fissh" group, by running

```bash
sudo gpasswd -a yourusername fissh
```

## On other distros
- Step 1
Create a new directory: /opt/FiSSH

- Step 2
Build FiSSH-Desktop in QT Creator (in Release mode) and copy the program to /opt/FiSSH, so that it can be run using the command /opt/FiSSH/FiSSH

- Step 3
Generate the SSL certificate (that will be used for encryption of messages between Android and PC apps):

```bash
sudo openssl req -newkey rsa:4096 -nodes -keyout /opt/FiSSH/key.pem -x509 -days 365 -out /opt/FiSSH/certificate.pem
```

- Step 4
Install the /usr/bin/fissh script and make it executable

```bash
#!/bin/bash
export SSH_ASKPASS="/opt/FiSSH/FiSSH"
setsid ssh "$@"
```

# Using FiSSH
- Step 1
Install the FiSSH android app on your phone and configure it with your computer's private IP and with the passphrase of the SSH key!

- Step 2 (optional)
Add the alias to .bashrc

```bash
alias ssh='fissh'
```

Now every time you use ssh, fissh will run, if you ever want to ssh without FiSSH, use /usr/bin/ssh


