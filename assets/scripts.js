window.onload = function() {
    var tabItem = document.getElementsByClassName("tab-item");

    var tabActive = function() {
        var ahref = this.getElementsByTagName('a')[0].getAttribute('href');
        ahref = ahref.replace('#', '');

        if (ahref !== '') {
            hideTabs();
            clearTabItem();
            this.classList.add('active');
            document.getElementById(ahref).classList.add('active');
        }
    };

    var hideTabs = function() {
        var tabContent = document.getElementsByClassName('tab-content');
        for (var i = 0; i < tabContent.length; i++) {
            tabContent[i].classList.remove('active');
        };
    }

    var clearTabItem = function() {
        for (var i = 0; i < tabItem.length; i++) {
            tabItem[i].classList.remove('active');
        };
    }

    for (var i = 0; i < tabItem.length; i++) {
        tabItem[i].addEventListener('click', tabActive, false);
    };

    var ipTypeLoad = function() {
        var ipType = document.getElementById('ipTypeWifi');
        var ipTypeClass = document.getElementsByClassName('ip-type');

        ipType.addEventListener('change', function() {
            if (this.value == 'Static') {
                for (let index = 0; index < ipTypeClass.length; index++) {
                    const element = ipTypeClass[index];
                    element.classList.add('active');
                }
            } else {
                for (let index = 0; index < ipTypeClass.length; index++) {
                    const element = ipTypeClass[index];
                    element.classList.remove('active');
                }
            }
        });

        if (ipType.value == 'Static') {
            for (let index = 0; index < ipTypeClass.length; index++) {
                const element = ipTypeClass[index];
                element.classList.add('active');
            }
        }
    };

    ipTypeLoad();

    // Broker Change
    // var broker_type = document.getElementById('broker-type-select');
    // var broker_custom = document.getElementById('broker-type-custom');
    // var broker_antares = document.getElementById('broker-type-antares');
    // if (broker_type.value == 'custom') {
    //     broker_custom.style.display = 'flex';
    //     broker_antares.style.display = 'none';
    // } else if (broker_type.value == 'antares') {
    //     broker_custom.style.display = 'none';
    //     broker_antares.style.display = 'flex';
    // }


    // document.getElementById('broker-type-select').onchange = function() {
    //     if (this.value == 'custom') {
    //         broker_custom.style.display = 'flex';
    //         broker_antares.style.display = 'none';
    //     } else if (this.value == 'antares') {
    //         broker_custom.style.display = 'none';
    //         broker_antares.style.display = 'flex';
    //     }
    // }


};

var logoutButton = function() {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "/logout", true);
    xhr.send();
    alert("Anda Berhasil Keluar..!");
    setTimeout(function() {
        window.open("/", "_self");
    }, 200);
}