
L'affichage est fait avec Raylib.
Je suis parti d'un template afin d'utiliser raylib :
https://www.youtube.com/watch?v=PaAcVk5jUd8
(a noter que ce template servait exclusivement a l'affichage)



Le programme tourne via un objet de la classe PetriDish, que l'on a ici nomme "DISH".
Toutes les methodes decrites plus bas s'appliquent a cet objet "DISH".



    Initialisation :

Le constructeur de PetriDish prend comme arguements la taille (w,h) de la grille.

La methode .DrawInit() initilialise l'affichage et prend comme arguement l'offset minimum
(c'est a dire la taille du coutour), la taille (w,h) de la fenetre, et facultativement
l'id d'une des deux colormap (1 ou 2).

Afin d'initialiser les concentration, il existe deux methode :
.Import_ConcentrationInit() importe les concentrations via une image (vert=A, bleu=B) et
prend comme arguement la source de cette image. (Trois templates sont disponibles dans le dossier.)
.Perlin_Perlin_ConcentrationInit() fait la meme chose sauf qu'elle genere elle-meme l'image
via un bruit perlin, et prend comme arguement l'echelle de ce bruit.

Afin de poser les parametres DA, DB, f, k, u et v,
on utilise les methodes .Set_DA(), .Set_DB(), .Set_f(), .Set_k(), .Set_u() et .Set_v().
Elle sont overloadees et prennent comme arguement :
soit la valeur homogene du parametre associe,
soit la source d'une image (de la meme maniere que .Import_ConcentrationInit()), ainsi que
les valeurs min et max du parametre.
On notera les canals de couleurs suivants pour chaque parametre :
DA = vert
DB = bleu
f = rouge
k = bleu
u = rouge
v = bleu
(voir notamment image "kf.png" utilisee comme gradient)



    Execution :

Pour executer le programme, on fait tourner la boucle "while (WindowShouldClose() == false)"
de raylib. (voir main.cpp)

Dans celle ci, la methode .Draw() affiche la grille sur la fenetre.
Afin de mettre a jour cette derniere, on utilise de concert :
.Diffuse()                      <- applique la diffusion
.GrayScott() ou .Brusselator()  <- applique la reaction
.Update()                       <- substitue t<-t+1



Des exemples de quelques experiences que j'ai pu faire sont disponibles ici :
...

