# Maintainer: Ioan Moldovan <ioan@member.fsf.org>

pkgname=fissh
pkgver=1.0.1
pkgrel=0

pkgdesc='SSH authentication via Android Fingerprint scanning (Desktop part)'
url='https://git.iodev.science/ioan/FiSSH-Desktop'
arch=('x86_64')
license=('MIT')

makedepends=('git','qt5-base')

source=('git+https://git.iodev.science/ioan/FiSSH-Desktop')
sha256sums=('SKIP')

build () {
    cd FiSSH-Desktop
    qmake
    make
}

package () {
    cd FiSSH-Desktop
    mkdir -p $pkgdir/opt/FiSSH
    cp FiSSH $pkgdir/opt/FiSSH/FiSSH 
    chmod +x $pkgdir/opt/FiSSH/FiSSH
    cp fissh-script $pkgdir/usr/bin/fissh
    chmod +x $pkgdir/usr/bin/fissh
}

post_install () {
    openssl req -newkey rsa:4096 -nodes -keyout /opt/FiSSH/key.pem -x509 -days 36500 -out /opt/FiSSH/certificate.pem    
    
    groupadd fissh
    useradd -M -r -g fissh -s /sbin/nologin fissh  

    chown fissh:fissh /opt/FiSSH/key.pem
    chmod 640 /opt/FiSSH/key.pem

    echo "!!! DO NOT FORGET !!!"
    echo
    echo "TO BE ABLE TO USE FiSSH YOU NEED TO ADD YOUR USER TO THE fissh GROUP!"
    echo
}
