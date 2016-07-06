% Test de rapport avec Pandoc
% Damien GABRIEL
% Refonte de juillet 2016

<!-- NE PAS METTRE D'ESPACE DANS LES FORMULES -->
<!-- Compiler avec 
pandoc -F pandoc-crossref -F pandoc-citeproc introduction.md -t html5 -s --mathjax --bibliography bblio_stage_L3.bib -o rapport_L3.html -->

# Ecoulement de Couette Plan, différents régimes et simulation #

L'écoulement de Couette plan est l'un des écoulement le plus simple, étant l'écoulement résultant du mouvement de deux plaques.

<!-- Faire le graph avec TikZ -->

Dans la suite, nous prendrons les notations suivantes pour les axes :

* x pour la direction du mouvement des plaques
* y pour la direction entre les deux plaques
* z pour une direction normale à x et y complétant la base

On défini le nombre de Reynolds, $\Re$, comme

$\Re = \frac{Uh}{\nu}$

Dans l'équation précédente :

* $U$ est la vitesse d'écoulement
* $\nu$ est la viscosité cinématique du fluide
* $h$ est la disatance entre les deux plaques

On peut aussi utiliser une défintion faisant intervenir le taux de cissaillement $\frac{U}{h}$ et l'interval $2h$ entre les plaques. Le nombre de Reynolds est alors donné par :

$$\Re = \frac{\frac{U}{h}(2h^2)}{\nu} = \frac{4Uh}{\nu}$$ {#eq:Reynolds}

L'utilisation de la formulation de l'équation ([@eq:Reynolds]) permet de mieux prendre en compte les phénomènes mis en oeuvre, les grandes structures turbulentes se développant sur la hauteur $2h$ du système. Dans la suite nous utiliserons cepandant la première défintion, plus traditionnelle.

<!-- Schéma des différents régimes dans l'écoulement de Couette plan -->

A faible nombre de Reynolds, jusque vers $R_{u} = 312$, l'écoulement est globalement stable et laminaire, toute perturbation relaxe rapidement. 

Pour des nombres de Reynolds élevés, au-delà de R_{t} = 415$, on observe une turbulence uniforme *«featureless turbulence»*

La region entre $R_{u}$ et $R_{t}$ peut à son tour être décomposée en différentes parties :

* de $R_{u} = 312$ à $R_{g} = 325$, la turbulence ne se maintient pas et le système revient à l'état laminaire au bout d'un temps éventuellement très long.
* de $R_{g} = 325$ à $R = 360$, des stries se forment dans les systèmes d'aspet suffisament grand et restent fragmentées. Comme dans tous les cas de turbulence au-delà de $R_{g}$, l'état peut se maintenir aussi longtemps que dure la manipulation.
* au-delà, les fragments se rejoignent et forment progressivement des stries continues, illustrées sur [TODO], qui s'estompent peu à peu pour laisser la place à une turbulence uniforme obtenue pour $R > R_{t} = 415$.

Expérimentalement, plusieurs techniques sont utilisées pour étudier la transition :

* Soit, en partant d'un état turbulent initial à nombre de Reynolds élevé, on abaisse brutalement le nombre de Reynolds (expérience de «trempe»)
* Soit, en partant d'un état laminaire, on crée des perturbations localisées d'amplitude finies dans l'écoulement
* On utilise aussi des écoulements de base modifiés par la présence de fils fins ou de perles dans l'écoulement à la limite ou ces obstacles sont très petits
`
Les résultats expérimentaux portent, dans la plupart des cas, sur la fraction turbulente, c'est-à-dire le rapport entre la surface occupée par la turbulence et la surface totale du domaine expérimental.

Les simulations numériques effectuées jusqu'à présent sont des résolutions brutes, tridimensionnelles, des équations de Navier-Stokes. Les systèmes sont le plus souvent petits, étant de l'ordre de la MFU *«Minimal Flow Unit»* qui correspond à la taille minimale permettant d'observer de la turbulence.

Une autre approche est la modélisation par une méthode de Galerkin.

* Limitée à la MFU, tel que dans [@waleffe1997self], elle s'intéresse aux systèmes dynamiques de petites dimensions et aux transitoires chaotiques. Cette approche permet de mettre en évidence les phénomènes locaux mais reste probablement hors de propos pour les systèmes de grande taille.

* Etendue à des systèmes de grande dimension mais au prix d'une faible résolution sur $y$ qui limite son utilisation à la partie basse du régime transitoire, au environ de $R_{g} = 325$. L'article [@manneville2005modeling] donne un exmple de cette approche. Les phénomènes ne sont reproduits que qualitativement.

L'objectif de ce stage est d'étudier la partie haute du régime transitoire dans les systèmes de grande taille par la simulation numérique directe des équations de Navier-Stokes *«Direct Navier-Stokes : DNS»* en diminuant la résolution à la plus petite valeur acceptable permettant de conserver la physique des phénomènes de façon quantitative bien qu'approchée.

Pour cela, mon travail a été réalisé en trois temps :

* Tout d'abord l'installation d'un code du domaine publique, ChannelFlow, sur les machines du LadHyX et la vérification de son fonctionnement correct
* Ensuite la modification du code en vue de l'étude des systèmes de grande taille
* Réalisation des mesures sur le code modifié et analyse
