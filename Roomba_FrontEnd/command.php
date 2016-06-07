<html>

<head>
	<title>control</title>
</head>

<body>

<style type="text/css">form, form div { display: inline; }</style>
<style>
body 
{ 
	background-color: #2F2F2F; 
}

.main 
{
  	width: 400px;
  	margin: 0px auto;
	background-color: #4F4F4F;
	border: 6px; border-color: #FFFFFF;
}
</style>


<div class="main">


<?php //pipe functions
	//functions
	function writep($command) 
	{
		echo "Command:".$command."<br />";
		if (!file_exists("/tmp/ptcFIFO")) 
		{
  			echo 'File not found';
		}
		else{
 			//stream_set_blocking($piper,false);
			$pipew = fopen("/tmp/ptcFIFO", 'w');
			
 			if(!$pipew) 
 			{
 				echo 'Can\'t open file';
 			}
			else 
 			{
 				//echo 'Success open file';
 				fwrite($pipew, $command);
				fclose($pipew);
 			}
	 		
		}
	}

	function readp()
	{

		if (!file_exists("/tmp/ctpFIFO")) {
  			echo 'File not found';
		}
		else if(!$piper = fopen("/tmp/ctpFIFO", 'r')) {
  			echo 'Can\'t open file';
		}
		else{
 		 	$recieved = fread($piper, "1"); 
			fclose($piper);
			return $recieved;
		}
		return(0);
	} 
?>


	
<form action="<?php echo $_SERVER['PHP_SELF']; //boven a?>" method="POST">
	<input type="hidden" name="knop" value="s">
	<input type="submit" value="start">
</form>
<form action="<?php echo $_SERVER['PHP_SELF']; //boven a?>" method="POST">
	<input type="hidden" name="knop" value="o">
	<input type="submit" value="stop">
</form>


</div>


</body>
</html>

