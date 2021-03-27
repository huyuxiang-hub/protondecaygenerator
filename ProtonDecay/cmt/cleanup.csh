# echo "cleanup ProtonDecay v0 in /afs/ihep.ac.cn/users/h/huyuxiang/junofs/branch/offline/Generator"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v2r0-branch/ExternalLibs/CMT/v1r26
endif
source ${CMTROOT}/mgr/setup.csh
set cmtProtonDecaytempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtProtonDecaytempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt cleanup -csh -pack=ProtonDecay -version=v0 -path=/afs/ihep.ac.cn/users/h/huyuxiang/junofs/branch/offline/Generator  $* >${cmtProtonDecaytempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt cleanup -csh -pack=ProtonDecay -version=v0 -path=/afs/ihep.ac.cn/users/h/huyuxiang/junofs/branch/offline/Generator  $* >${cmtProtonDecaytempfile}"
  set cmtcleanupstatus=2
  /bin/rm -f ${cmtProtonDecaytempfile}
  unset cmtProtonDecaytempfile
  exit $cmtcleanupstatus
endif
set cmtcleanupstatus=0
source ${cmtProtonDecaytempfile}
if ( $status != 0 ) then
  set cmtcleanupstatus=2
endif
/bin/rm -f ${cmtProtonDecaytempfile}
unset cmtProtonDecaytempfile
exit $cmtcleanupstatus

