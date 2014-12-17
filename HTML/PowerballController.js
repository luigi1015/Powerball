function PowerballController($scope, $location) 
{
	var pbJSON = '{' +
'"fileFormatVersion": 0.1,' +
'"numbers":[' +
'	{"number": 5, "month": 12, "day": 13, "year": 2014, "type": "0"},' +
'	{"number": 13, "month": 12, "day": 13, "year": 2014, "type": "0"},' +
'	{"number": 43, "month": 12, "day": 13, "year": 2014, "type": "0"},' +
'	{"number": 55, "month": 12, "day": 13, "year": 2014, "type": "0"},' +
'	{"number": 28, "month": 12, "day": 13, "year": 2014, "type": "0"},' +
'	{"number": 33, "month": 12, "day": 13, "year": 2014, "type": "1"},' +
'	{"number": 3, "month": 12, "day": 13, "year": 2014, "type": "2"},' +
'	{"number": 48, "month": 12, "day": 10, "year": 2014, "type": "0"},' +
'	{"number": 34, "month": 12, "day": 10, "year": 2014, "type": "0"},' +
'	{"number": 55, "month": 12, "day": 10, "year": 2014, "type": "0"},' +
'	{"number": 44, "month": 12, "day": 10, "year": 2014, "type": "0"},' +
'	{"number": 54, "month": 12, "day": 10, "year": 2014, "type": "0"},' +
'	{"number": 10, "month": 12, "day": 10, "year": 2014, "type": "1"},' +
'	{"number": 2, "month": 12, "day": 10, "year": 2014, "type": "2"},' +
'	{"number": 43, "month": 12, "day": 6, "year": 2014, "type": "0"},' +
'	{"number": 22, "month": 12, "day": 6, "year": 2014, "type": "0"},' +
'	{"number": 49, "month": 12, "day": 6, "year": 2014, "type": "0"},' +
'	{"number": 15, "month": 12, "day": 6, "year": 2014, "type": "0"},' +
'	{"number": 12, "month": 12, "day": 6, "year": 2014, "type": "0"},' +
'	{"number": 14, "month": 12, "day": 6, "year": 2014, "type": "1"},' +
'	{"number": 2, "month": 12, "day": 6, "year": 2014, "type": "2"},' +
'	{"number": 54, "month": 12, "day": 3, "year": 2014, "type": "0"},' +
'	{"number": 30, "month": 12, "day": 3, "year": 2014, "type": "0"},' +
'	{"number": 32, "month": 12, "day": 3, "year": 2014, "type": "0"},' +
'	{"number": 46, "month": 12, "day": 3, "year": 2014, "type": "0"},' +
'	{"number": 25, "month": 12, "day": 3, "year": 2014, "type": "0"},' +
'	{"number": 26, "month": 12, "day": 3, "year": 2014, "type": "1"},' +
'	{"number": 3, "month": 12, "day": 3, "year": 2014, "type": "2"},' +
'	{"number": 13, "month": 11, "day": 29, "year": 2014, "type": "0"},' +
'	{"number": 30, "month": 11, "day": 29, "year": 2014, "type": "0"},' +
'	{"number": 24, "month": 11, "day": 29, "year": 2014, "type": "0"},' +
'	{"number": 42, "month": 11, "day": 29, "year": 2014, "type": "0"},' +
'	{"number": 48, "month": 11, "day": 29, "year": 2014, "type": "0"},' +
'	{"number": 27, "month": 11, "day": 29, "year": 2014, "type": "1"},' +
'	{"number": 2, "month": 11, "day": 29, "year": 2014, "type": "2"},' +
'	{"number": 46, "month": 11, "day": 26, "year": 2014, "type": "0"},' +
'	{"number": 17, "month": 11, "day": 26, "year": 2014, "type": "0"},' +
'	{"number": 22, "month": 11, "day": 26, "year": 2014, "type": "0"},' +
'	{"number": 16, "month": 11, "day": 26, "year": 2014, "type": "0"},' +
'	{"number": 54, "month": 11, "day": 26, "year": 2014, "type": "0"},' +
'	{"number": 35, "month": 11, "day": 26, "year": 2014, "type": "1"},' +
'	{"number": 5, "month": 11, "day": 26, "year": 2014, "type": "2"},' +
'	{"number": 37, "month": 11, "day": 1, "year": 1997, "type": "0"},' +
'	{"number": 28, "month": 11, "day": 1, "year": 1997, "type": "0"},' +
'	{"number": 33, "month": 11, "day": 1, "year": 1997, "type": "0"},' +
'	{"number": 22, "month": 11, "day": 1, "year": 1997, "type": "0"},' +
'	{"number": 25, "month": 11, "day": 1, "year": 1997, "type": "0"},' +
'	{"number": 20, "month": 11, "day": 1, "year": 1997, "type": "1"}' +
']}';

	$scope.pbObj = JSON.parse(pbJSON);
	//console.log( $scope.pbObj );

	$scope.whiteballCounts = [];
	$scope.whiteballCounts.length = 59;
	for( i = 0; i < $scope.whiteballCounts.length; i++ )
	{
		$scope.whiteballCounts[i] = 0;
	}

	$scope.powerballCounts = [];
	$scope.powerballCounts.length = 35;
	for( i = 0; i < $scope.powerballCounts.length; i++ )
	{
		$scope.powerballCounts[i] = 0;
	}

	$scope.powerplayCounts = [];
	$scope.powerplayCounts.length = 59;
	for( i = 0; i < $scope.powerplayCounts.length; i++ )
	{
		$scope.powerplayCounts[i] = 0;
	}

	for( i = 0; i < $scope.pbObj.numbers.length; i++ )
	{
		if( $scope.pbObj.numbers[i].type == "0" )
		{
			$scope.whiteballCounts[$scope.pbObj.numbers[i].number-1] = $scope.whiteballCounts[$scope.pbObj.numbers[i].number-1] + 1;
		}
		else if( $scope.pbObj.numbers[i].type == "1" )
		{
			$scope.powerballCounts[$scope.pbObj.numbers[i].number-1]++;
		}
		else if( $scope.pbObj.numbers[i].type == "2" )
		{
			$scope.powerplayCounts[$scope.pbObj.numbers[i].number-1]++;
		}
	}
}
