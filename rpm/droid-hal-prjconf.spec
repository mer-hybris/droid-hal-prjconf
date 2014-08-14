Name:       droid-hal-prjconf
Summary:    Project configs for Droid HAL adaptations for OBS
Version:    0
Release:    1
Group:      Configs
License:    GPLv2
Source0:    %{name}-%{version}.tar.bz2
Provides:   project-config

%description
%{summary}.

%prep
%setup -q -n %{name}-%{version}

%install
rm -rf %{buildroot}
mkdir -p $RPM_BUILD_ROOT/%{_datadir}/prjconf
cp -rf prjconf/prjconf.xml $RPM_BUILD_ROOT/%{_datadir}/prjconf/

%files
%defattr(-,root,root,-)
%{_datadir}/prjconf/*.xml

