# echo "setup ProtonDecay v0 in /afs/ihep.ac.cn/users/h/huyuxiang/junofs/branch/offline/Generator"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v2r0-branch/ExternalLibs/CMT/v1r26; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtProtonDecaytempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmtProtonDecaytempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt setup -sh -pack=ProtonDecay -version=v0 -path=/afs/ihep.ac.cn/users/h/huyuxiang/junofs/branch/offline/Generator  -no_cleanup $* >${cmtProtonDecaytempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt setup -sh -pack=ProtonDecay -version=v0 -path=/afs/ihep.ac.cn/users/h/huyuxiang/junofs/branch/offline/Generator  -no_cleanup $* >${cmtProtonDecaytempfile}"
  cmtsetupstatus=2
  /bin/rm -f ${cmtProtonDecaytempfile}
  unset cmtProtonDecaytempfile
  return $cmtsetupstatus
fi
cmtsetupstatus=0
. ${cmtProtonDecaytempfile}
if test $? != 0 ; then
  cmtsetupstatus=2
fi
/bin/rm -f ${cmtProtonDecaytempfile}
unset cmtProtonDecaytempfile
return $cmtsetupstatus

