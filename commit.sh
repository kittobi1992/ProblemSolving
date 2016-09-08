while getopts 'm:' OPTION ; do
	case "$OPTION" in
		m)
			printf "Commit-Message:\t\t $OPTARG \n"
			m=$OPTARG;;
	esac
done

bash -x clean.sh
git add -A
git commit -m "$m"
git push -u https://kittobi1992:pomaggier123@github.com/kittobi1992/ProblemSolving.git master