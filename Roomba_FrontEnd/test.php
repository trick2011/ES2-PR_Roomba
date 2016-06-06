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
<form action="<?php echo $_SERVER['PHP_SELF']; //boven a?>" method="POST">
	<input type="hidden" name="knop" value="s">
	<input type="submit" value="start roomba">
</form>
<form action="<?php echo $_SERVER['PHP_SELF']; //boven a?>" method="POST">
	<input type="hidden" name="knop" value="o">
	<input type="submit" value="stop roomba">
</form><br>

<?php //refresh
	//refresh rate
	$url=$_SERVER['REQUEST_URI']; header("Refresh: 2; URL=$url"); 
?>

<?php
	if(isset($_POST["knop"])){
		//echo "<h1>".$_POST["knop"] . "</h1>";
		writep($_POST["knop"]);
		}
	#else
		#echo "automatische refresh"."<br />";	
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

	function readp()
	{

		if (!file_exists("/tmp/ctpFIFO")) 
		{
  			echo 'File not found';
		}
		else if(!$piper = fopen("/tmp/ctpFIFO", 'r')) 
		{
  			echo 'Can\'t open file';
		}
		else 
		{
 		 	//echo 'Success open file';
 		 	$recieved = fread($piper, "1"); 
			//echo $recieved;
			//fflush($piper);
			fclose($piper);
			return $recieved;
		}
		//stream_set_blocking($piper,false);
		
	/* test stuff
		$arr=array("z","y","w","x","v","a","b","c");
		$i=rand(0,7);
		$recieved=$arr[$i]; */
		return(0);
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

<?php //kind a main?
	//recieved
	$val = readp();
	//echo "<h1>". $val . "</h1>";
	switch ($val) {
			case 'v':
				echo "Bump right detected". "<br />"; 
				echo '<img src="icons/bumpright.png" width = "400">'. "<br />";
				break;
			case 'w':
				echo "Bump left detected". "<br />";
				echo '<img src="icons/bumpleft.png" width = "400">'. "<br />";
				break;
			case 'x':
				echo "Drop detected". "<br />";
				echo '<img src="icons/roomba_full.png" width = "400">'. "<br />";
				break;
			case 'y':
				echo "Trashbin is full". "<br />";
				echo '<img src="icons/roomba_full.png" width = "400">'. "<br />";
				break;
			case 'z':
				echo "Battery is running low". "<br />";
				echo '<img src="icons/roomba_full.png" width = "400">'. "<br />";
				break;
			default:
				echo "<br />";
				echo '<img src="icons/roomba_full.png" width = "400">'. "<br />";
			//msg();
			break;
	}
?> 
<div align="center">
	
<form action="<?php echo $_SERVER['PHP_SELF']; //boven a?>" method="POST">
	<input type="hidden" name="knop" value="a">
	<input type="submit" value="voor">
</form>
<form action="<?php echo $_SERVER['PHP_SELF']; //links c?>" method="POST">
	<input type="hidden" name="knop" value="c">
	<input type="submit" value="   links  ">
</form>
<form action="<?php echo $_SERVER['PHP_SELF']; //rechts b?>" method="POST">
	<input type="hidden" name="knop" value="b">
	<input type="submit" value="rechts">
</form>
<form action="<?php echo $_SERVER['PHP_SELF']; //onder d?>" method="POST">
	<input type="hidden" name="knop" value="d">
	<input type="submit" value="achter">
</form><br>

<form action="<?php echo $_SERVER['PHP_SELF']; //stop k?>" method="POST">
	<input type="hidden" name="knop" value="j">
	<input type="submit" value="stop">
</form><br>

<form action="<?php echo $_SERVER['PHP_SELF']; //autoclean e?>" method="POST">
	<input type="hidden" name="knop" value="e">
	<input type="submit" value="autoclean">
</form>
<form action="<?php echo $_SERVER['PHP_SELF']; //spotclean g?>" method="POST">
	<input type="hidden" name="knop" value="g">
	<input type="submit" value="spotclean">
</form>
<form action="<?php echo $_SERVER['PHP_SELF']; //walltrace h?>" method="POST">
	<input type="hidden" name="knop" value="h">
	<input type="submit" value="walltrace">
</form>

<form action="<?php echo $_SERVER['PHP_SELF']; //dock k?>" method="POST">
	<input type="hidden" name="knop" value="k">
	<input type="submit" value="dock">
</form>

</div>


</body>
</html>

