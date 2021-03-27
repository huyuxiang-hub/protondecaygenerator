# echo "cleanup ProtonDecay v0 in /afs/ihep.ac.cn/users/h/huyuxiang/junofs/branch/offline/Generator"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v2r0-branch/ExternalLibs/CMT/v1r26; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtProtonDecaytempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmtProtonDecaytempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt cleanup -sh -pack=ProtonDecay -version=v0 -path=/afs/ihep.ac.cn/users/h/huyuxiang/junofs/branch/offline/Generator  $* >${cmtProtonDecaytempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt cleanup -sh -pack=ProtonDecay -version=v0 -path=/afs/ihep.ac.cn/users/h/huyuxiang/junofs/branch/offline/Generator  $* >${cmtProtonDecaytempfile}"
  cmtcleanupstatus=2
  /bin/rm -f ${cmtProtonDecaytempfile}
  unset cmtProtonDecaytempfile
  return $cmtcleanupstatus
fi
cmtcleanupstatus=0
. ${cmtProtonDecaytempfile}
if test $? != 0 ; then
  cmtcleanupstatus=2
fi
/bin/rm -f ${cmtProtonDecaytempfile}
unset cmtProtonDecaytempfile
return $cmtcleanupstatus

