<!DOCTYPE html>

<!--  chmod a+rw <fifo file> -->

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
    $fifo = "/tmp/FIFO"; 
    $msg = "message"; 
//WRITE
    	$pipe = fopen($fifo, 'a');
    		if ( $pipe == false) 
        		echo "Cannot open fifo";
    		else 
        		echo 'Can write fifo';
	fwrite($pipe, $msg);
	fclose($pipe);
	sleep(1);
//READ
/*    	$pipe = fopen($fifo, 'r');
    		if ( $pipe == false) 
        		echo "Cannot open fifo";
    		else 
        		echo 'Can read fifo'; 
	//$contents = fread($pipe, "4");
	//echo fread($pipe, "4");
	echo readfile($pipe);
	fclose($pipe);
	//print $contents;
*/



/*
$fifo = '/tmp/FIFO'; 
[Thu Apr 14 19:58:06.078660 2016] [:error] [pid 3396] [client 192.168.20.159:57459] PHP Warning:  fopen(/tmp/FIFO): failed to open stream: Permission denied in /var/www/html/php/pipew.php on line 24
[Thu Apr 14 19:58:06.078728 2016] [:error] [pid 3396] [client 192.168.20.159:57459] PHP Warning:  fwrite() expects parameter 1 to be resource, boolean given in /var/www/html/php/pipew.php on line 29
[Thu Apr 14 19:58:06.078751 2016] [:error] [pid 3396] [client 192.168.20.159:57459] PHP Warning:  fclose() expects parameter 1 to be resource, boolean given in /var/www/html/php/pipew.php on line 30
[Thu Apr 14 19:58:17.178843 2016] [:error] [pid 7158] [client 192.168.20.159:57462] PHP Warning:  fopen(/tmp/FIFO): failed to open stream: Permission denied in /var/www/html/php/pipew.php on line 24, referer: http://tarick-ms-7599/php/pipew.php
[Thu Apr 14 19:58:17.178947 2016] [:error] [pid 7158] [client 192.168.20.159:57462] PHP Warning:  fwrite() expects parameter 1 to be resource, boolean given in /var/www/html/php/pipew.php on line 29, referer: http://tarick-ms-7599/php/pipew.php
[Thu Apr 14 19:58:17.178971 2016] [:error] [pid 7158] [client 192.168.20.159:57462] PHP Warning:  fclose() expects parameter 1 to be resource, boolean given in /var/www/html/php/pipew.php on line 30, referer: http://tarick-ms-7599/php/pipew.php
*/
?>