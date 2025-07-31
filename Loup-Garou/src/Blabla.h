void Blabla(){
    int i,x,y;
    srand(time(NULL));
    i = rand()%22;
    switch(i){
        case 0 :
        printf("Par une sombre nuit d'automne vous décidez d'aller visiter une maison hantée par le fantôme\n d'un phacochère unijambiste (pas ouf l'idée).Une fois arrivé sur place vous êtes soudainement très\n fatigué, afin d'assouvir votre envie de sommeil deux choix s'offrent à vous.\nChoix 1 : La maison hantée est bien trop effrayante pour vous et vous décidez de rentrer chez vous.\nChoix 2 : La maison hantée vous convient parfaitement et vous n'avez pas le courage de marcher jusqu'à chez vous.\n");
         do{
             printf("\nEntrez votre choix (1 ou 2) : ");
             scanf("%d", &x);
         }while(x<1||x>2);
         if(x==1){
             printf("\nLes 45 minutes de marche qui séparent la maison hantée de votre maison vous semblent interminable,\n mais vous parvenez néanmoins à rejoindre votre domicile. Vous vous endormez paisiblement dans votre lit et faites de beaux rêves\n");
             printf("Entrez 1 puis retournez dormir"); 
             scanf("%d", &x);
         }
         else{
             printf("\nVous entrez dans la maison hantée et en visitez chaque pièce afin de trouver une chambre pour la nuit.\n Après 15 minutes de recherche vous tombez sur une chambre d'enfant et vous décidez d'y dormir. \nVous vous installez dans le lit et vous endormez paisiblement...\nMais malheureusement vous ne vous réveillerez jamais.\n");
             printf("Entrez 1 puis retournez dormir"); 
             scanf("%d", &x);
         }
         break;
         case 1 :
         printf("Aimez vous les pâtes ?\nEntrez 1 pour OUI \nEntrez 2 pour NON \n");
         do{
             printf("\nEntrez le numéro :");
             scanf("%d", & x);
         }while(x<1||x>2);
         if(x==1){
             printf("\nVous les préferez avec ou sans sauce ? \nEntrez 1 si vous préférez avec \nEntrez 2 si vous préférez sans\n");
             do{
                 printf("\nEntrez le numéro : ");
                 scanf("%d", & y);
             }while(y<1||y>2);
             printf("\nC'est cool\n");
             printf("Entrez 1 puis retournez dormir"); 
             scanf("%d", &x);
         }
         else{
             printf("\nC'est pourtant délicieux, vous avez goûts alimentaires douteux\n");
             printf("Entrez 1 puis retournez dormir"); 
             scanf("%d", &x);
         }
         break;
         case 2:
         printf("Savez vous que la pieuvre possède trois coeurs, deux coeurs branchiaux et un coeur principal\n");
         printf("Entrez 1 puis retournez dormir"); 
         scanf("%d", &x);
         break;
         case 3:
         printf("Le soleil se couche \nLa Lune est pleine \nLes loups appellent \nLes loups-garous se réveillent \nHurlant à la Lune \nMarchand dans la brume \nTuant avec douleur \nL'humain remplie de peur.\n");
         printf("Entrez 1 puis retournez dormir"); 
         scanf("%d", &x);
         break;
         case 4:
         printf("Vous êtes un âne, vous vous promenez tranquillement en ville à la recherche de vêtements chaud pour \nl'hiver qui arrive à grand pas. En vous promenant vous tombez sur votre magasin de friandises favori.\n Vous observez toutes les sucreries du magasin avec envie et vous êtes tenté d'en acheter. \nMais en sortant votre portefeuille vous remarquez que vous n'avez pas assez d'argent pour acheter des\n vêtements et des bonbons. Vous devez donc choisir entre les friandises et les vêtements.\nTapez 1 pour acheter des bonbons \nTapez 2 pour acheter des vêtements.\n");
        do{
            printf("\nEntrez votre choix : ");
            scanf("%d", & x);
        }while(x<1||x>2);
        if(x==1){
            printf("\nVous décidez sans trop réfléchir d'acheter des bonbons.\n Malheureusement pour vous quelques jours plus tard l'hiver est arrivé, et n'ayant rien pour vous \ncouvrir vous êtes mort de froid.\n");
        }
        else{
            printf("\nVous décidez après mûre réflexion de vous rendre dans la boutique de vêtements pour âne la plus proche\n et d'acheter un magnifique manteau arc-en-ciel. Vous passez donc un merveilleux hiver.\n");
        }
        printf("Entrez 1 puis retournez dormir"); 
        scanf("%d", &x);
        break;
         case 5:
         printf("\nOù se trouvent les glandes sudoripares d'un chien ? \n1 - Dans sa gueule \n2 - A l'arrière de son cerveau \n3 - Sous ses pattes \n4 - Derrière ses reins\n");
         do{
             printf("\nEntrez le numéro de la réponse : ");
             scanf("%d", & x);
         }while(x<0||x>4);
         if(x==3){
             printf("\nBonne réponse\n");
         }
         else{
             printf("\nMais non !!! Les glandes sudoripares d'un chien se trouvent sous ses pattes voyons.\n");
         }
         printf("Entrez 1 puis retournez dormir"); 
         scanf("%d", &x);
         break;
         case 6:
         printf("Savez vous que la langue de la baleine bleue peut peser autant qu'un éléphant soit environ 2,7 tonnes\n et que son coeur peut peser jusqu'à près d'une tonne.\n");
         printf("Entrez 1 puis retournez dormir"); 
         scanf("%d", &x);
         break;
         case 7:
         printf("Vous êtes une grenouille et vous sautez de nénuphars en nénuphars. Au loin vous apercevez un scorpion,\n vous decidez donc d'aller lui parler. Le scorpion vous explique qu'il a besoin de votre aide pour \ntraverser la rivière. Il vous demande alors s'il peut monter sur votre dos. Mais vous connaissez cet\n animal et vous savez que sa piqûre est mortelle c'est pourquoi vous lui demandez de ne pas vous \npiquer. Le scorpion vous promet qu'il ne vous piquera pas mais à vous de faire votre choix.\n Acceptez vous d'aider le scorpion ? \nChoix 1 : OUI \nChoix 2 : NON \n");
         do{
             printf("\nEntrez votre choix : ");
             scanf("%d", & x);
         }while((x<1)||(x>2));
         if(x==1){
             printf("\nVous décidez de venir en aide au scorpion, mais une fois sur votre dos le scorpion vous pique. \nVous mourez donc tous les deux.\n");
         }
         else{
             printf("\nVous décidez de ne pas venir en aide au scorpion, et continuez votre route vers d'autres aventures.\n");
         }
         printf("Entrez 1 puis retournez dormir"); 
         scanf("%d", &x);
         break;
         case 8:
         printf("Qui a fondé l'Académie Française ? \n1 - Louis XIII \n2 - Le cardinal de Richelieu \n3 - Louis XIV \n4 - Jul \n");
         do{
             printf("\nEntrez le numéro de la réponse : ");
             scanf("%d", & x);
         }while((x<0)||(x>4));
         if(x==2){
             printf("\nBonne réponse\n");
         }
         else{
             printf("\nMais NON voyons !! L'académie française a été créé par le cardinal de Richelieu.\n");
         }
         printf("Entrez 1 puis retournez dormir"); 
         scanf("%d", &x);
         break;
         case 9:
         printf("Savez vous que la guerre la plus courte de l'histoire n'a duré que 38 minutes.\n");
         printf("Entrez 1 puis retournez dormir"); 
         scanf("%d", &x);
         break;
         case 10:
         printf("\nUn bruit vous réveille ça vient de l'église\n\n1=Rester au lit\n2=Vérifier que tout se passe bien à la fenêtre ");
         do{
             printf("\nVeuillez entrez un choix : ");
             scanf("%d",&x);
         } while(x<1||x>2);
         if(x == 1){
             printf("Les bruits commencer à s'éloigner.\n");
         } else {
        printf("Vous voyez des bêtes terrifiantes et retourner en panique dans votre lit.\n"); 
         }
         printf("Entrez 1 puis retournez dormir"); 
         scanf("%d", &x);
         break;
         case 11:
         printf("Un proverbe romain dit “La lumière montre l'ombre et la vérité le mystère.”\n");
         printf("Entrez 1 puis retournez dormir"); 
         scanf("%d", &x);
         break;
         case 12:
         printf("\nVous penser à la premier personne qui vous viens à l'esprit et imaginer passer votre vie avec.\n\n1=c'est un rêve.\n2=c'est un cauchemars.");
         do{
             printf("\nVeuillez entrez un choix : ");
             scanf("%d",&x);
         } while(x<1||x>2);
         printf("Entrez 1 puis retournez dormir"); 
         scanf("%d", &x);
         break;
         case 13:
         printf("Le loup est un animal nocturne qui vit en meute dirigée la plupart du temps par un mâle dominant.\nLes loups communiquent entre eux par des hurlements et des grondements.\n");
         printf("Entrez 1 puis retournez dormir"); 
         scanf("%d", &x);
         break;
         case 14:
         printf("La transformation en loup-garou s’appelle la lycanthropie. \nMais il faut préciser qu'il existe une maladie mentale aussi appelée lycanthropie, bien connue en psychiatrie et reconnue scientifiquement. \nLe patient croit qu'il peut se transformer en loup. On parle alors de lycanthropie clinique.\n");
         printf("Entrez 1 puis retournez dormir"); 
         scanf("%d", &x);
         break;
         case 15:
         printf("\nVous rêvez d'un forêt en feu\n\n1=La regarder brûler car vous ne pouvez rien faire.\n2=Essayer tant bien que mal d’arrêter le feu.");
         do{
             printf("\nVeuillez entrez un choix : ");
             scanf("%d",&x);
         } while(x<1||x>2);
         if(x == 1){
             printf("Il n'y a rien a faire vous avez raison.\n");
         } else {
             printf("Il n'y a rien a faire c'est trop tard.\n");
         }
         printf("Entrez 1 puis retournez dormir"); 
         scanf("%d", &x);
         break;
         case 16:
         printf("Il reste en 2020 : 580 loups sur le territoire français.\n");
         printf("Entrez 1 puis retournez dormir"); 
         scanf("%d", &x);
         break;
         case 17:
         printf("\nVous rêver d'une sorcière qui dit une phrase incompréhensible.\n\n1=Vous acquissiez\n2=Vous essayez de lui répondre.");
         do{
             printf("\nVeuillez entrez un choix : ");
             scanf("%d",&x);
         } while(x<1||x>2);
         if(x == 1){
             printf("Elle rit et part.\n");
         } else {
             printf("Elle semble fier de vous et puis part.\n"); 
         }
         printf("Entrez 1 puis retournez dormir"); 
         scanf("%d", &x);
         break;
         case 18:
         printf("\nVous rêver d'une voyante qui vous demande de choisir une couleur :\n\n1=Bleu\n2=Rouge\n3=Vert");
         do{
             printf("\nVeuillez entrez un choix : ");
             scanf("%d",&x);
         } while(x<1||x>3);
         if(x == 1){
             printf("Elle vous annonce que votre mort est proche.\n");
         } else if(x == 2) {
             printf("Selon elle un ange gardien veille sur vous.\n"); 
         } else {
             printf("La nuit va être agiter selon elle.\n");
         }
         printf("Entrez 1 puis retournez dormir"); 
         scanf("%d", &x);
         break;
         case 19:
         printf("Vous vous réveillez en pleine nuit, il fait froid et le village est silencieux quelque chose cloche.\n");
         printf("Entrez 1 puis retournez dormir"); 
         scanf("%d", &x);
         break;
         case 20:
         printf("\nVous rêvez d'un loup blanc qui vous fixe.\n\n1=S'approcher\n2=Le fuir\n");
         do{
             printf("\nVeuillez entrez un choix : ");
             scanf("%d",&x);
         } while(x<1||x>2);
         if(x == 1){
             printf("Vous vous approchez et le caresser, il n'a pas l'air agressif.\n");
         } else {
             printf("Vous courez le plus vite possible, mais il n'a pas l'air de vous suivre.\n"); 
         }
         printf("Entrez 1 puis retournez dormir"); 
         scanf("%d", &x);
         break;
         case 21:
         printf("\nVous rêvez d'un champ de fleur.\n\n1=Courir le plus vite possible\n2=Se cacher de quelque chose\n");
         do{
             printf("\nVeuillez entrez un choix : ");
             scanf("%d",&x);
         } while(x<1||x>2);
         if(x == 1){
         printf("Un éclair frappe là où vous étiez installé ! C'était moins une.\n");
         } else {
         printf("Un éclair vous frappe ! Au moins, la foudre ne tombe jamais 2 fois au même endroit.\n"); 
         }
         printf("Entrez 1 puis retournez dormir"); 
         scanf("%d", &x);
         break;
         default:
         printf("Savez vous que d'après la légende le pape Adrien IV est mort en avalant une mouche.\n");
         printf("Entrez 1 puis retournez dormir"); 
         scanf("%d", &x);
         break;
    }
    system("clear");
}