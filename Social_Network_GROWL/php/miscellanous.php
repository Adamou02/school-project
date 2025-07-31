<?php
    define('MISC_INCLUDED','1');
    
    function java_log(string $log) {
      if(db_selectColumns(table_name:'user',columns:['IsAdmin'],filters:['UserID' => ['LIKE', '"'.$_SESSION['connected'].'"','0']])[0][0] == 1){
         $log = str_replace("'", '"', $log);
         ?> 
            <script>
               console.log('<?=$log?>');
            </script>
         <?php
      }
   }

   function php_err(string $err) {
      $_SESSION["php_error_log"] = $err;
      java_log($err);
      die($err);
   }

   function redirect(string $location) {
      header('Location: '.$location, true, 301);
      exit;
   }

   function array_equal($a, $b) {
      return (
         is_array($a) 
         && is_array($b) 
         && count($a) == count($b) 
         && array_diff($a, $b) === array_diff($b, $a)
      );
   }
?>