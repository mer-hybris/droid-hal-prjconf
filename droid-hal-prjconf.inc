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

cp -f $SRC_GENERIC/prjconf.inc $DEST

# The syntax inside the project configuration is not XML but RPM-like.
# Instead of the xml extension the inc extension makes more sense here,
# support both file extensions.
for ext in inc xml ; do
    if [ -e $SRC_SPECIFIC/prjconf.$ext ]; then
        if grep -q "^Macros:" $SRC_SPECIFIC/prjconf.$ext; then
            echo "prjconf.$ext must not contain Macros section. Put them to macros.$ext"
            exit -1
        fi
        cat $SRC_SPECIFIC/prjconf.$ext >> $DEST
    fi
done

echo "Macros:" >> $DEST

for ext in inc xml ; do
    if [ -e $SRC_SPECIFIC/macros.$ext ]; then
        grep -v "^Macros:" $SRC_SPECIFIC/macros.$ext >> $DEST
    fi
done

%files
%defattr(-,root,root,-)
%{_datadir}/prjconf/*.xml

