#! /bin/bash

echo "*** Installing $DISTRO buildtime dependencies ***";
  case "$DISTRO" in
    Debian|Ubuntu)
      sudo apt-get $YesOpt install \
        python3.6 python3-pip
      ;;
    Fedora)
      yum $YesOpt install \
        python3.6 python3-pip
      ;;
    RedHatEnterprise*|CentOS)
      yum $YesOpt install epel-release;
      yum $YesOpt install \
        rh-python3.6 python3-pip
      ;;
    *) echo "ERROR: Unknown or Unsupported $DISTRO $CODENAME release, please report to the mailing list"; exit 1;;
  esac ;;
  pip3 install --upgrade pip \
  pip3 install scancode-toolkit
  