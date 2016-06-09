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
	background-image: url(./pics/2d9660406-roomba880-2.nbcnews-ux-2880-1000.jpg);">
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
<button onclick="goBack()">Go Back</button>
<br>

<?php
	if(isset($_POST["knop"])){
		//echo "<h1>".$_POST["knop"] . "</h1>";
		writep($_POST["knop"]);
		}
	else
		#echo "automatische refresh"."<br />";	
		echo " "."<br / >";
?>

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
?>

<script>
	function msg() 
	{
		alert("ERROR");
	}
</script>
<script>
	function goBack() 
	{
		window.history.back();
	}	
</script>

<div align="center">
	
<form action="<?php echo $_SERVER['PHP_SELF']; //boven a?>" method="POST">
	<input type="hidden" name="knop" value="S">
	<input type="submit" value="STOP ROOMBA CONTROLLER">
</form>
<form action="<?php echo $_SERVER['PHP_SELF']; //links c?>" method="POST">
	<input type="hidden" name="knop" value="U">
	<input type="submit" value="😇">
</form>
</div>


</body>
</html>

