# Blender
Blender Game 

Les 9 règles a implémenter Blunder :
∙ Blunder part de l’endroit indiqué par le caractère @ sur la carte et se dirige vers le SUD.
∙ Blunder termine son parcours et meurt lorsqu’il rejoint la cabine à suicide notée $.
∙ Les obstacles que Blunder peut rencontrer sont représentés par # ou X.
∙ Lorsque Blunder rencontre un obstacle, il change de direction en utilisant les priorités suivantes : SUD,
EST, NORD et OUEST. Il essaie donc d’abord d’aller au SUD, s’il ne peut pas il va à l’EST, s’il ne peut
toujours pas il va au NORD, et finalement s'il ne peut toujours pas il va à l’OUEST.
∙ Sur son chemin, Blunder peut rencontrer des modificateurs de trajectoire qui vont lui faire changer
instantanément de direction. Le modificateur S l'orientera désormais vers le SUD, E vers l’EST, N vers le
NORD et W vers l’OUEST.
∙ Les inverseurs de circuits (I sur la carte) produisent un champ magnétique qui vont inverser les priorités
de direction que Blunder devrait choisir à la rencontre d’un obstacle. Les priorités deviendront OUEST,
NORD, EST, SUD. Si Blunder retourne sur un inverseur I, les priorités repassent à leur état d’origine
(SUD, EST, NORD, OUEST).
∙ Blunder peut aussi trouver quelques bières sur son parcours (B sur la carte) qui vont lui donner de la
force et le faire passer en mode Casseur. Le mode Casseur permet à Blunder de détruire et de traverser
automatiquement les obstacles représentés par le caractère X (uniquement les obstacles X). Lorsqu’un
obstacle est détruit, il le reste définitivement et Blunder conserve sa direction. Si Blunder est en mode
Casseur et qu’il passe à nouveau sur une bière, il perd aussitôt son mode Casseur. Les bières restent en
place après le passage de Blunder.
∙ 2 téléporteurs T peuvent être présents dans la ville. Si Blunder passe sur un téléporteur, il est
automatiquement téléporté à la position de l’autre téléporteur et il conserve ses propriétés de direction et
de mode casseur.
Commentaires
Dans ce projet, j’utilise uniquement la librairie std.
J’utilise les template via cette std.
Je construit essentiellement 2 Objets principaux :
• l’objet Map ( la carte de jeu avec les différents objets)
• l’objet Blunder
Le point important de ce projet est le test des fonctionnalités. Pour cela, j’ai généré des cartes de jeux
aléatoires. ( j’ai mis un minimum de checks: obligation d’avoir un début :@) mais la génération peut
écraser des données
• Un unit test pour la fonction de génération. Rand simple.
• Un fonctionnel test pour tester le jeu sur 1000 cartes.
