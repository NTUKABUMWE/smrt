<?php
$host="localhost";
$username = "root"; 
$password = "";     
$dbname = "iot_project";
$conn = mysqli_connect($host, $username, $password, $dbname);
if($con){
    echo "server connection successful";
}
else{
    echo"server failed to coonect";
}
$select=mysqli_query($con,"select * from senssor_data");
if(mysqli_num_rows($select)>0){
    ?>
    <table border="1">
        <th><td>NUMBER</td><td>HUMIDITY</td><td>TEMPERATURE</td><td>TIME</td></th>
</table>
<?php
while($data=mysqli_fetch_array($select)){
?>
<tr><td><?php echo $data["id"];?></td></tr><td><?php echo $data["humidity"];?></td><td><?php echo $data["temperature"];?></td><td><?php echo $data["time"];?></td>
 <?

}

?>
</table>
<?php
}
?>
