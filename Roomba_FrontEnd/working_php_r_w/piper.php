<!DOCTYPE html>
<html>
<?php $url=$_SERVER['REQUEST_URI']; header("Refresh: 10; URL=$url"); ?>
<!-- <meta http-equiv="refresh" content="10"> -->

<head></head>
<body class="page_bg">



Today's date is <?php echo date("d-m-Y H:i:s"); ?><br>

<button onclick="myFunction()">HELLO</button><br>
<script>function myFunction() {}</script> 

<?php echo $_SERVER["REMOTE_ADDR"];?><br>

</body>

<?php
    $fifo = "/tmp/FIFO"; 
    //$msg = "message";
//READ
	//echo fopen($fifo, 'r');
    	$pipe = fopen($fifo, 'r');
    		if ( $pipe == false) 
        		echo "Cannot open fifo";
    		else 
        		echo 'Can read fifo'; 
	//$contents = fread($pipe, "4");
	echo "\n";
	echo fread($pipe, "7"); // deze werkt
	
	//echo readfile($pipe); // PHP Warning:  readfile() expects parameter 1 to be a valid path, resource given in /var/www/html/php/pipe.php on line 32, referer: http://tarick-ms-7599/php/pipe.php
	fclose($pipe);
	//print $contents;
?>
