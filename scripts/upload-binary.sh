#if [ "$TRAVIS_PULL_REQUEST" == "false" ]; then
  echo -e "Starting to update gh-pages\n"

  #copy data we're interested in to other place
  mkdir -p $HOME/$TRAVIS_BUILD_NUMBER 
  cp -R .pioenvs/nodemcuv2/firmware.elf $HOME/$TRAVIS_BUILD_NUMBER/firmware.elf

  #go to home and setup git
  cd $HOME
  git config --global user.email "travis@travis-ci.org"
  git config --global user.name "Travis"

  #remove old clone if exists
  rm -rf gh-pages

  #using token clone gh-pages branch
  git clone --quiet --branch=gh-pages https://${GH_TOKEN}@github.com/ciandt-dev/garage-kelvin-celsius.git  gh-pages > /dev/null

  #go into diractory and copy data we're interested in to that directory
  cd $HOME/gh-pages
  mkdir -p $HOME/gh-pages/build/$TRAVIS_BUILD_NUMBER
  cp -Rf $HOME/$TRAVIS_BUILD_NUMBER/* $HOME/gh-pages/build/$TRAVIS_BUILD_NUMBER

  #add, commit and push files
  git add -f .
  git commit -m "Travis build $TRAVIS_BUILD_NUMBER pushed to gh-pages"
  git push -fq origin gh-pages > /dev/null

  echo -e "Done.\n"
#fi


ls $HOME/gh-pages/build/$TRAVIS_BUILD_NUMBER