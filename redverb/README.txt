Voici l'architecture du projet.

+---build // Répertoire de construction de la dll pour les différents OS
¦   +---linux
¦   +---mac
¦   ¦   +---JuceDemoPlugin.xcodeproj
¦   +---win32
¦       +---Debug
¦       +---Release // ici se trouvera la dll (redverb.dll)
¦       +---_UpgradeReport_Files
+---src // ici se trouvent les sources à modifier
    +---juce // ici se trouvent les sources de juce

Pour l'instant, on bosse avec VS2008 Pro. Le .sln marche out of the box
chez moi.

