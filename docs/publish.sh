prepare() {
    git config --global user.email "omniavinco@gmail.com"
    git config --global user.name "travis-ci"
    git config push.default simple
    mkdir -p .travis
    openssl aes-256-cbc -K $encrypted_4b7a7054081f_key -iv $encrypted_4b7a7054081f_iv -in id_rsa.enc -out id_rsa -d
    chmod 600 .travis/id_rsa
    eval `ssh-agent -s`
    ssh-add .travis/id_rsa
    virtualenv .venv
    . ./.venv/bin/activate
    pip install ghp-import
}

publish() {
    cd docs
    doxygen doxygen.conf
    git remote remove origin
    git remote add origin git@github.com:Perlmint/libbasehangul.git
    git fetch origin
    ghp-import out/html
    git push origin gh-pages
    cd ..
}
