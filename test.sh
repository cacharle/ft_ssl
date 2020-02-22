#!/bin/sh

test_status=0

red() {
	echo "$(tput setaf 1)$1$(tput sgr 0)\c"
	test_status=1
}

green() {
	echo "$(tput setaf 2)$1$(tput sgr 0)\c"
}

assert() {
	if [ $# -ne 2 ]; then
		red "[KO] "
		return 0
	fi
	if [ -z "$1" ]; then
		red "[KO] "
		return 0
	fi
	if [ -z "$2" ]; then
		red "[KO] "
		return 0
	fi
	if [ "$1" = "$2" ]; then
		green "[OK] "
	else
		red "[KO] "
	fi
}

# assert_ok() {
# 	assert $1 "OK"
# }
#
# assert_error() {
# 	assert $1 "Error"
# }
#

assert_md5() {
	assert `./ft_ssl md5 $1 2>&1` `md5 $1 2>&1`
}

assert_sha256() {
	assert `./ft_ssl md5 $1 2>&1` `openssl sha -sha256 $1 2>&1`
}

echo "Usage: \c"
assert "`./ft_ssl 2>&1`" "usage: ./ft_ssl command [command opts] [command args]"
assert "`./ft_ssl foo 2>&1`"<<EOF
ft_ssl: Error: 'foo' is an invalid command.

Standard commands:

Message Digest commands:
md5
sha256

Cipher commands:

EOF


echo "\nArgument Error: \c"
assert_md5 "-a"
assert_md5 "-foo"
assert_md5 "-foo foobar.tmp"
assert_md5 "-foo README.md"
assert_md5 "foobar.tmp"

echo "\nFiles: \c"
assert_md5 "README.md"
assert_md5 "README.md LICENCE"
assert_md5 "README.md foobar.tmp LICENCE"

echo "\nQuiet: \c"
assert_md5 "-q foobar.tmp"
assert_md5 "-q README.md"
assert_md5 "-q README.md LICENCE"
assert_md5 "-q README.md foobar.tmp LICENCE"

echo "\nString: \c"
assert_md5 "-s bonjour"
assert_md5 "-s bonjour -s 'aurevoir'"
assert_md5 "-sbonjour -s'aurevoir'"
assert_md5 "-s\"bonjour\" -syo'aurevoir'"

echo "\nReverse: \c"
assert_md5 "-r -s bonjour"
assert_md5 "-r -s bonjour -s 'aurevoir'"
assert_md5 "-sbonjour -rs'aurevoir'"
assert_md5 "-r -rs\"bonjour\" -syo'aurevoir'"
assert_md5 "-r README.md"
assert_md5 "README.md -r LICENCE"
assert_md5 "README.md -r fowbar.tmp -r LICENCE"
assert_md5 "-q -r README.md"

echo "\nPipe: \c"
echo "yoyoyo" | assert_md5 "-p -r -s bonjour"
echo "vvvvvvvvvv" | assert_md5 "-sbonjour -p -rs'aurevoir'"
echo "asdfkajhsdfjh" | assert_md5 "-p README.md -r fowbar.tmp -r LICENCE"
echo "helpplz" | assert_md5 "-p -r README.md"

exit $test_status
