echo -n "Enter 1st Number : "
read -r num1
echo -n "Enter 2nd Number : "
read -r num2
echo -n "Enter operator : "
read -r operator

case $operator in
	"+") result=$((num1+num2))
	;;

	"-") result=$((num1-num2))
	;;

	"*") result=$((num1*num2))
	;;
	
	"/") result=$((num1/num2))
	;;
esac

echo "The Result $num1 $operator $num2 = $result"


