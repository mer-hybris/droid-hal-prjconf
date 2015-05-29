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
rm -rf %{buildroot}
DIR=$RPM_BUILD_ROOT/%{_datadir}/prjconf
PRJCONF=$DIR/prjconf.xml
mkdir -p $DIR
cp -rf droid-hal-prjconf/prjconf/prjconf.xml $DIR
if [ -e prjconf/device-specific.xml ]; then
  echo >> $PRJCONF
  echo "# %{device}-specific content:" >> $PRJCONF
  cat prjconf/device-specific.xml >> $PRJCONF
fi

%files
%defattr(-,root,root,-)
%{_datadir}/prjconf/*.xml

