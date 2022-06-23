<?php

$dbname = 'id18229280_scaledata';
$dbuser = 'id18229280_ilyes84000';  
$dbpass = '0123456789aB!'; 
$dbhost = 'localhost'; 

$conn = mysqli_connect($dbhost,$dbuser,$dbpass,$dbname);//on se connecte a la BDD
$api_key_value = "tPmAT5Ab3j7F9";
 
$api_key = $lecture= $lecture_avg = "";
$lecture = $_POST["lecture"];
$lecture_avg = $_POST["lecture_avg"];
$sql = "INSERT INTO espdata (lecture,lecture_avg) VALUES ('" . $lecture . "', '" . $lecture_avg . "');";


if(mysqli_query($conn,$sql)){
    echo "enregistrement crée avec succés";
    echo "<br>";
    echo "$lecture";
}
else{
    echo "erreur lors de l'enregistrement";
    echo "<br>";
    echo "$lecture";
}

echo "<br>";
echo "<table border='1', cellspacing='0'>";
foreach($result as $row)
{
    echo "<tr>";
    echo "<td>id:$row[id]</td><td> lecture:$row[lecture]</td><td> lecture_avg:$row[lecture_avg]</td><td> date:$row[date]</td>";
    echo "</tr>";
}
echo "</table>";
