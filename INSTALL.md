# System Requirements
* Linux (Windows will NOT work, Mac I don't know)
* QT Creator
* OpenSSH/LibreSSH/Something-SSH (just needs to have the "ssh" binary)
configured to use a KEY protected with a PASSPHRASE (which you will have to enter into the Android app!)
* Static LAN ip on your computer (look at /etc/network/interfaces)


# How to install FiSSH?
- Step 1
Install the FiSSH android app on your phone and configure it with your computer's private IP and with the passphrase of the SSH key!

- Step 2
Create a new directory: /opt/FiSSH

- Step 3
Build FiSSH-Desktop in QT Creator (in Release mode) and copy the resulting binary to /opt/FiSSH, so the program can be run using the command /opt/FiSSH/FiSSH

- Step 4
Generate the SSL certificate (that will be used for encryption of messages between Android and PC apps):

```bash
sudo openssl req -newkey rsa:2048 -nodes -keyout /opt/FiSSH/key.pem -x509 -days 365 -out /opt/FiSSH/certificate.pem
```

- Step 5
Install the /usr/bin/fissh script and make it executable

```bash
#!/bin/bash
export SSH_ASKPASS="/opt/FiSSH/FiSSH"
setsid ssh $@
```

- Step 6
Add the alias to .bashrc

```bash
alias ssh='fissh'
```

# That was easy! :D (just a joke)

