<?php
        if(!defined('SESSION_START')) {
              session_start();
              define('SESSION_START','1');
       }

       if(file_exists("./php/constant.php")) { 
              set_include_path('./php');
       }
       if(!defined('CONSTANTE_INCLUDED')) 
              include_once("./constant.php");
       if(!defined('SESSION_INCLUDED'))  
              include_once(SESSION);      
       if(!defined('MISC_INCLUDED')) 
              include_once(MISC);
       if(!defined('DATABASE_INCLUDED')) 
              include_once(DATABASE);
?>