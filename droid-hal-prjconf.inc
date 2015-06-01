Name:       droid-hal-prjconf-%{device}
Summary:    Project configs for %{device} Droid HAL adaptation for OBS
Version:    0
Release:    1
Group:      Configs
License:    BSD-3-Clause
Source0:    %{name}-%{version}.tar.bz2
Provides:   project-config

%description
%{summary}.

%prep
%setup -q -n %{name}-%{version}

%install
CONFDIR=prjconf
SUBMODULE=droid-hal-prjconf
SRC_GENERIC=$SUBMODULE/$CONFDIR
SRC_SPECIFIC=$CONFDIR
DESTDIR=$RPM_BUILD_ROOT/%{_datadir}/$CONFDIR
DEST=$DESTDIR/prjconf.xml

rm -rf %{buildroot}
mkdir -p $DESTDIR

if [ grep -q "^Macros:" $SRC_GENERIC/prjconf.xml $SRC_SPECIFIC/prjconf.xml ]; then
    echo "prjconf.xml must not contain Macros section. Put them to macros.xml"
    exit -1
fi

cp -f $SRC_GENERIC/prjconf.xml $DEST
if [ -e $SRC_SPECIFIC/prjconf.xml ]; then
    cat $SRC_SPECIFIC/prjconf.xml >> $DEST
fi

cat $SRC_GENERIC/macros.xml >> $DEST
if [ -e $SRC_SPECIFIC/macros.xml ]; then
    cat $SRC_SPECIFIC/macros.xml | grep -v "^Macros:" >> $DEST
fi

%files
%defattr(-,root,root,-)
%{_datadir}/prjconf/*.xml

