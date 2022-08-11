# Net code example
This project is my coursework, in which I needed to create a simple network shooter. In this project, I fully used all my project architecture building skills as well as my skills working with UE4 network tools. The game is based on client-server interaction technology and the use of predicates on clients.

At the start, the player is greeted by a simple visual interface offering to find a dedicated server and connect to it, or to play a game.

![](https://lh3.googleusercontent.com/jUjgSZ6eZuuR5dBj7b2yhcL_9V8oDSyAnJ96U5D_rcqnWrUUoM2637LzK_GvN6WGCfmNtl4l1c9iV-LYrgct0DCxF5l32SWevUcw3OnrkOTvB3cXuJjnMr2271Nl2BuwtsXBg4PLrcigqrJc-iveufqB1tn3RUOnGF171HcUHszsQaUjB0Vk_2K-QrTw604Ff1cM5JnjJt1_Wq6uJ6twMlS6zHjFpndaFtsG0qF4nnTcccfkhJOmJxPCT-uq38JV_ftI8ACFEogQ5UCYizQc0mwio00YzDee-D4RZMK5K6Z-M-vP0T1JBmYcq-IW7Obqsk3469MvcuEexbw9l2N3vjJ5ZJm_54cU99nnJxV1qB3K3RgZiMmpTpnrVqfFXD0_LWYnzDB5FBQ1qkrhUYmL-WAXN1Zsyafdgvjq24K13D7eP3obuXtQc0oAXVrZfcQ-bptRBPamJsiqSIJxGSK7xJ2slw2v7LJhZr4V9wf2vMB_9AAFpTXY3HCG1ju8Y8uaLYjXe67j8ovRg3ToeWkYlBKQJ6YUJo7jJb-CAUZTHMkWu3-LrAH0j0mR2DGVKJlydPXC25wSgsz_dtNUJH0c3Ndm7nQmRJYjLtVe6XOK9dPL8j5XptE0i7lCch20J8BUcwzCC_gfRdLpw4W3Kq0oGQvDmLHKlw1Kw-k54hHaCs0XarSAkRVW-1WZUKKqDQ33Gx_1qJ8ZGUWctNANSAl71s3SYAV9gBK5fPJzzHkT6dcuXLUwuKf3qy4mCzM=w2335-h1268-no?authuser=0)

At the same time, a dedicated server must be running on one of the local machines. The connection is made directly by IP.

![](https://lh3.googleusercontent.com/5zFfHc3POB0-wseTnaQF2vwGKZNmCBeRrDgEmuOv1aWUydh-FNExQ5m0M-re4xOcS6zqNENPrQizqqRQnbAdSiDfbUPR1ONNYKgGVyfECxizcSwJxUp-PZMKKpdWWgLdw3wYeyhWKpgjMuBJbAkrU97RhsghqHTW5JrjSAGAxZUBqQZOn8TQ7oFfkG3-CUkmU5UvzLjJoV4Jclrz7E8wnk98NRuWsrfMneckZfI39BC6Vo20pWwVi11SyQmRdOlT75wHL9h-97m9bYFjYJf9V_73rxtuqIBijH-MAjpgyjBCB4XGfz9OoFEnt6qIRQ3RyA1p4MUqm3uD5yoHe0-L5zm2fnyghqFWCWzgLdase2_VhISZogRmsv_c7hMOJwZxA6hHoVsH-cl54GOt_12nHA0ci64q0PVIPQgJyCPrrvIp7SDDo-i3xzcdgNy0PKYC7CdlJJboaPWC7xp8zl7CTyR6K39HTzhaOu-zxvC97i0oTGt96ZM28hDPZzUO6WQTSuc_juk5lC6wjVxBY-q7xeXbsb7Th0a14k_DRv3e6rAaxETpzn5NXjH1tSWTLhNVlGA__7qIW2_aWQ7Y_X8YLmjZXPcLoP0SOhfXS3IC3upnEmDPYc4pzSarmPNxsIczWTC6OZf_S3YjDpgYqbELomXz7QVRLF_E-bnDDyC5csXNHYpXFP8o5eEfxdE3IyIcsUat1-3422vVkymM5d3Viq9xOv1T1HGVZbfi0t_4dnguZ78KGQaw67PY7cY=w1463-h639-no?authuser=0)

The gameplay is built on the basis of the every man for himself mode. All players, as they connect to the server, will spawn on the map. They have one weapon (a submachine gun). Players can jump, shoot, aim and run, while running, you can not aim and shoot, and if you run while shooting or aiming, then shooting or aiming will stop. Players can also jump and aim weapons. When a player is hit, his health bar in the lower left corner decreases. When a player runs out of health, he dies and is instantly resurrected at one of the resurrection points.

![](https://lh3.googleusercontent.com/HlwSDQF4dmz4fOT9D-GQ_3Wvx0fRMuR-WaCT-fZ5bSgVU8UnolpnrWzROYl2GFMxzyKUc3V49cdxsV1MlLvD8Fkz0iJoLbT-JxfHGL4VpAQwUefOYsOiSI77Dpg_S7uhKJo58y00-M8qGfDJAZqQQoUn76dmXH0B3w-fHpMgPHECKDh9POQBbmMD4tMmWkvehih4L7GyNC7rgy2PXyfGpoYvJu6uEkbOtpjjKYZZVVxyS9yeRvzXYjTWbh50iwu5zHTGKTwkgL5qawgzBCsYFAMkhbvzAxYQ_TeF0-QM7d1uyQ3p50f9Abd-Ad0GuX2QNBqmsFVdgQVmRJZaLCABOJly-FIefC5591YycK136zGm6jHzk-xza0jCIAiq4VKMpAR7QI2WJfw1ObH3o8axBdL7APjYmzajRWOpP658zLjzbUM49YyIZSeCsDyieThXcFWAXnXGMJP8MSr-0tg_W25GqkJRFR12l_XrEaDLv-Uppw6q6o13wHU12s20dWi7og7iWULunXXh8VWITWOvJH-JJn6TZZlOehbfH4p4HFFXgf_UBzET5NBDU-8-4o9xo4Wolrra_O44J-haQ8aSrJAtBrtbFQJDGlfVadcfvYWyv2WGeC0MFuMq6gdNepQz7eh4tQClHjkHclGjMa-zJlcNmV7Z4cK4ZpWzi7OG-wtmPsOKp0pT8OQbpUa4uXJjevuxahQuFOZLyRSw51DGEMGkY346jO4LZzzbRoMBp-9BpfdSytC6E9STBv4=w2337-h1268-no?authuser=0)
![](https://lh3.googleusercontent.com/TjALpQb7AURHjAirLdN_4R6dVYFWBETCkkNUOzJ47kPbXvr_iQpCH7tk0zIGpNnJ3VNOWLjPL5ne5d09pZycGBw6vI3807N_giU2K-v1skSDulA0wf4XcNRf_RgU3N78cBY6HeLgSEMsO8dclb7lGUv-DWorYJcdyR2uCFzAfzY9DsInCpRoDBh6ouqq3HHEVym7xvQKDKCMe0k22dzVlAOIm3tJQCWz9kpdD980q86V44LBYmum4mrxceqRM-DagNHdGAe_EmJufEUB-BDbshspJCRy14a7DAG7CC2F89cjRBKfQwpPYt8hN4fsuWqupEsccPlMGLyENyboMS3NDIowjrBIJ76wsUDLhYFT7wWf2ySQ_bOwFaFlDsEFKCBeWRrjhTReWm5jJuMZpEz3AKFctfwAenmAjb8YFRGfka1hpB3h8sIq5nz_28_Os4BtJg8DlGPG3HPiIdRUUl9PXQtgkGnX_WIHByQVnRxUALVjQFJauIWOiNIySsSFNWpvNJ-2smmhVw0doKk1SOhFKM8KdDZD0DeXb7Mcan7MHu8Jbupb0sIntiwmur3K4sMOEvFlM6CrU_jrfssh7i6h8ruNIpugoAVl5ihybr5VpR7LhUf6w6E22XPWaB7UfwG2xpuMdP1JaHG9ouGv35bO00QOJh5vT1dzOty-DhYxoTRpJZW3ze6LVEq_QrJBlZB2peFBV9WpgUWDroIkCIJCD0olZQAxCkBBejYFx05n3OOtzRx8ISGWsed8yzI=w2254-h1269-no?authuser=0)

In the pictures you can see how client 1 aims and shoots.
