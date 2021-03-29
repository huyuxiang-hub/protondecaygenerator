#-- start of make_header -----------------

#====================================
#  Application ProtonDecay
#
#   Generated Mon Mar 29 11:09:07 2021  by huyuxiang
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_ProtonDecay_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_ProtonDecay_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_ProtonDecay

ProtonDecay_tag = $(tag)

#cmt_local_tagfile_ProtonDecay = $(ProtonDecay_tag)_ProtonDecay.make
cmt_local_tagfile_ProtonDecay = $(bin)$(ProtonDecay_tag)_ProtonDecay.make

else

tags      = $(tag),$(CMTEXTRATAGS)

ProtonDecay_tag = $(tag)

#cmt_local_tagfile_ProtonDecay = $(ProtonDecay_tag).make
cmt_local_tagfile_ProtonDecay = $(bin)$(ProtonDecay_tag).make

endif

include $(cmt_local_tagfile_ProtonDecay)
#-include $(cmt_local_tagfile_ProtonDecay)

ifdef cmt_ProtonDecay_has_target_tag

cmt_final_setup_ProtonDecay = $(bin)setup_ProtonDecay.make
cmt_dependencies_in_ProtonDecay = $(bin)dependencies_ProtonDecay.in
#cmt_final_setup_ProtonDecay = $(bin)ProtonDecay_ProtonDecaysetup.make
cmt_local_ProtonDecay_makefile = $(bin)ProtonDecay.make

else

cmt_final_setup_ProtonDecay = $(bin)setup.make
cmt_dependencies_in_ProtonDecay = $(bin)dependencies.in
#cmt_final_setup_ProtonDecay = $(bin)ProtonDecaysetup.make
cmt_local_ProtonDecay_makefile = $(bin)ProtonDecay.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)ProtonDecaysetup.make

#ProtonDecay :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'ProtonDecay'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = ProtonDecay/
#ProtonDecay::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of application_header

ProtonDecay :: dirs  $(bin)ProtonDecay${application_suffix}
	$(echo) "ProtonDecay ok"

cmt_ProtonDecay_has_prototypes = 1

#--------------------------------------

ifdef cmt_ProtonDecay_has_prototypes

ProtonDecayprototype :  ;

endif

ProtonDecaycompile : $(bin)deex.o $(bin)ProtonDecayGen.o ;

#-- end of application_header
#-- start of application

$(bin)ProtonDecay${application_suffix} :: $(bin)deex.o $(bin)ProtonDecayGen.o $(use_stamps) $(ProtonDecay_stamps) $(ProtonDecaystamps) $(use_requirements)
	$(link_echo) "application $@"
	$(link_silent) $(cpplink) -o $(@).new $(bin)deex.o $(bin)ProtonDecayGen.o $(cmt_installarea_linkopts) $(ProtonDecay_use_linkopts) $(ProtonDecaylinkopts) && mv -f $(@).new $(@)

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

install_dir = ${CMTINSTALLAREA}/$(tag)/bin
ProtonDecayinstallname = ProtonDecay${application_suffix}

ProtonDecay :: ProtonDecayinstall ;

install :: ProtonDecayinstall ;

ProtonDecayinstall :: $(install_dir)/$(ProtonDecayinstallname)
ifdef CMTINSTALLAREA
	$(echo) "installation done"
endif

$(install_dir)/$(ProtonDecayinstallname) :: $(bin)$(ProtonDecayinstallname)
ifdef CMTINSTALLAREA
	$(install_silent) $(cmt_install_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(ProtonDecayinstallname)" \
	    -out "$(install_dir)" \
	    -cmd "$(cmt_installarea_command)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

##ProtonDecayclean :: ProtonDecayuninstall

uninstall :: ProtonDecayuninstall ;

ProtonDecayuninstall ::
ifdef CMTINSTALLAREA
	$(cleanup_silent) $(cmt_uninstall_action) \
	    -source "`(cd $(bin); pwd)`" \
	    -name "$(ProtonDecayinstallname)" \
	    -out "$(install_dir)" \
	    -cmtpath "$($(package)_cmtpath)"
endif

#	@echo "------> (ProtonDecay.make) Removing installed files"
#-- end of application
#-- start of dependencies ------------------
ifneq ($(MAKECMDGOALS),ProtonDecayclean)
ifneq ($(MAKECMDGOALS),uninstall)
ifneq ($(MAKECMDGOALS),ProtonDecayprototype)

$(bin)ProtonDecay_dependencies.make : $(use_requirements) $(cmt_final_setup_ProtonDecay)
	$(echo) "(ProtonDecay.make) Rebuilding $@"; \
	  $(build_dependencies) -out=$@ -start_all $(src)deex.cc $(src)ProtonDecayGen.cc -end_all $(includes) $(app_ProtonDecay_cppflags) $(lib_ProtonDecay_cppflags) -name=ProtonDecay $? -f=$(cmt_dependencies_in_ProtonDecay) -without_cmt

-include $(bin)ProtonDecay_dependencies.make

endif
endif
endif

ProtonDecayclean ::
	$(cleanup_silent) \rm -rf $(bin)ProtonDecay_deps $(bin)ProtonDecay_dependencies.make
#-- end of dependencies -------------------
#-- start of cpp ------

ifneq (,)

ifneq ($(MAKECMDGOALS),ProtonDecayclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)deex.d

$(bin)$(binobj)deex.d :

$(bin)$(binobj)deex.o : $(cmt_final_setup_ProtonDecay)

$(bin)$(binobj)deex.o : $(src)deex.cc
	$(cpp_echo) $(src)deex.cc
	$(cpp_silent) $(cppcomp)  -o $@ $(use_pp_cppflags) $(ProtonDecay_pp_cppflags) $(app_ProtonDecay_pp_cppflags) $(deex_pp_cppflags) $(use_cppflags) $(ProtonDecay_cppflags) $(app_ProtonDecay_cppflags) $(deex_cppflags) $(deex_cc_cppflags)  $(src)deex.cc
endif
endif

else
$(bin)ProtonDecay_dependencies.make : $(deex_cc_dependencies)

$(bin)ProtonDecay_dependencies.make : $(src)deex.cc

$(bin)$(binobj)deex.o : $(deex_cc_dependencies)
	$(cpp_echo) $(src)deex.cc
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(ProtonDecay_pp_cppflags) $(app_ProtonDecay_pp_cppflags) $(deex_pp_cppflags) $(use_cppflags) $(ProtonDecay_cppflags) $(app_ProtonDecay_cppflags) $(deex_cppflags) $(deex_cc_cppflags)  $(src)deex.cc

endif

#-- end of cpp ------
#-- start of cpp ------

ifneq (,)

ifneq ($(MAKECMDGOALS),ProtonDecayclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)ProtonDecayGen.d

$(bin)$(binobj)ProtonDecayGen.d :

$(bin)$(binobj)ProtonDecayGen.o : $(cmt_final_setup_ProtonDecay)

$(bin)$(binobj)ProtonDecayGen.o : $(src)ProtonDecayGen.cc
	$(cpp_echo) $(src)ProtonDecayGen.cc
	$(cpp_silent) $(cppcomp)  -o $@ $(use_pp_cppflags) $(ProtonDecay_pp_cppflags) $(app_ProtonDecay_pp_cppflags) $(ProtonDecayGen_pp_cppflags) $(use_cppflags) $(ProtonDecay_cppflags) $(app_ProtonDecay_cppflags) $(ProtonDecayGen_cppflags) $(ProtonDecayGen_cc_cppflags)  $(src)ProtonDecayGen.cc
endif
endif

else
$(bin)ProtonDecay_dependencies.make : $(ProtonDecayGen_cc_dependencies)

$(bin)ProtonDecay_dependencies.make : $(src)ProtonDecayGen.cc

$(bin)$(binobj)ProtonDecayGen.o : $(ProtonDecayGen_cc_dependencies)
	$(cpp_echo) $(src)ProtonDecayGen.cc
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(ProtonDecay_pp_cppflags) $(app_ProtonDecay_pp_cppflags) $(ProtonDecayGen_pp_cppflags) $(use_cppflags) $(ProtonDecay_cppflags) $(app_ProtonDecay_cppflags) $(ProtonDecayGen_cppflags) $(ProtonDecayGen_cc_cppflags)  $(src)ProtonDecayGen.cc

endif

#-- end of cpp ------
#-- start of cleanup_header --------------

clean :: ProtonDecayclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(ProtonDecay.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

ProtonDecayclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_application ------
	$(cleanup_echo) application ProtonDecay
	-$(cleanup_silent) cd $(bin); /bin/rm -f ProtonDecay${application_suffix}
#-- end of cleanup_application ------
#-- start of cleanup_objects ------
	$(cleanup_echo) objects ProtonDecay
	-$(cleanup_silent) /bin/rm -f $(bin)deex.o $(bin)ProtonDecayGen.o
	-$(cleanup_silent) /bin/rm -f $(patsubst %.o,%.d,$(bin)deex.o $(bin)ProtonDecayGen.o) $(patsubst %.o,%.dep,$(bin)deex.o $(bin)ProtonDecayGen.o) $(patsubst %.o,%.d.stamp,$(bin)deex.o $(bin)ProtonDecayGen.o)
	-$(cleanup_silent) cd $(bin); /bin/rm -rf ProtonDecay_deps ProtonDecay_dependencies.make
#-- end of cleanup_objects ------
