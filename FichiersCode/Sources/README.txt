Fonctionnement temporel de main.c :

Etape 1 : 
	Déclaration des variables globales et des structures

Etape 2 (dans main()) : 
	Configuration des structures (GPIO, Timers)
	Initialisation des GPIO (Clock Enable etc)
	Lancement des Timers (PWM, compteur)

Etape 3 :
	Entrée dans la boucle while(1) en attendant les interruptions


Interruption Callback() :
	Récupération de la commande du plateau transmise par la télécommande
	Configuration "à la volée" de la PWM du moteur du plateau en fonction des données