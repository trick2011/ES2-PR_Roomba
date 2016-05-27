
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
<button onclick="goBack()">Go Back</button><br>

<?php //refresh
	//refresh rate
	$url=$_SERVER['REQUEST_URI']; header("Refresh: 2; URL=$url"); 
	/*MSG to myself
		metas are a fail, dont use. 
		al tough its easy,php doesnt handel them wel
		alter img just by php dipshit*/
?>

<?php
	if(isset($_POST["knop"])){
		//echo "<h1>".$_POST["knop"] . "</h1>";
		writep($_POST["knop"]);
		}
	else
		echo "automatische refresh"."<br />";	
?>

<?php //pipe functions
	//var
 	$fifow = "/tmp/wFIFO"; //write
	$fifor = "/tmp/rFIFO"; //read

	//functions
	function writep($command) 
	{
	echo "Command:".$command."<br />";
    		$pipew = fopen($fifow, 'a');
    			if ( $pipe == false) 
        			echo "Cannot open wfifo";
    			else 
        			echo 'Can write fifo';
		fwrite($pipew, $command);
		fclose($pipew);
	}

	function readp()
	{/*
		$piper = fopen($fifor, 'r');
    			if ( $piper == false) 
        			echo "Cannot open rfifo";
    			else 
        			echo 'Can read fifo'; 
		$recieved = fread($piper, "1"); 
		fclose($piper);
	*/
		$arr=array("z","y","w","x","v","a","b","c");
		$i=rand(0,7);
		$recieved=$arr[$i];
		return $recieved;
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

	
<form action="<?php echo $_SERVER['PHP_SELF']; //boven a?>" method="POST">
	<input type="hidden" name="knop" value="a">
	<input type="submit" value="boven">
</form>
<form action="<?php echo $_SERVER['PHP_SELF']; //rechts b?>" method="POST">
	<input type="hidden" name="knop" value="b">
	<input type="submit" value="rechts">
</form>
<form action="<?php echo $_SERVER['PHP_SELF']; //links c?>" method="POST">
	<input type="hidden" name="knop" value="c">
	<input type="submit" value="   links  ">
</form>
<form action="<?php echo $_SERVER['PHP_SELF']; //onder d?>" method="POST">
	<input type="hidden" name="knop" value="d">
	<input type="submit" value="onder">
</form><br>

<form action="<?php echo $_SERVER['PHP_SELF']; //stop k?>" method="POST">
	<input type="hidden" name="knop" value="j">
	<input type="submit" value="stop">
</form><br>

<form action="<?php echo $_SERVER['PHP_SELF']; //autoclean e?>" method="POST">
	<input type="hidden" name="knop" value="e">
	<input type="submit" value="autoclean">
</form>
<form action="<?php echo $_SERVER['PHP_SELF']; //cellclean f?>" method="POST">
	<input type="hidden" name="knop" value="f">
	<input type="submit" value="cellclean">
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

