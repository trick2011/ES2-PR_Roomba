<!DOCTYPE html>
<html>
<?php $url=$_SERVER['REQUEST_URI']; header("Refresh: 10; URL=$url"); ?>
<meta http-equiv="refresh" content="10">

<head></head>
<body class="page_bg">



Today's date is <?php echo date("d-m-Y H:i:s"); ?><br>

<button onclick="myFunction()">HELLO</button><br>
<script>function myFunction() {}</script> 

<?php echo $_SERVER["REMOTE_ADDR"];?><br>

</body>

<?php

    $fifo = '/tmp/LeFIFO'; 
    $msg = "message"; 


//READ
    	$pipe = fopen($fifo, 'r');
    		if ( $pipe == false) 
        		echo "Cannot open fifo";
    		else 
        		echo 'Can read fifo'; 
	//$contents = fread($pipe, "4");
	//echo fread($pipe, "4");
	echo readfile($pipe);
	fclose($pipe);

	//print $contents;
?>









