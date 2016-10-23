angular.module('acApp', [])
  .controller('AcController', ['$interval', '$http', function ($interval, $http) {
    var vm = this;
    vm.temp = "-";
    vm.hum = "-";
    vm.tempControl = 24;
    vm.votes = [];
    vm.status = "";

    getTemp = function () {
      var req = {
        method: 'GET',
        url: '/api/status'
      };

      $http(req).then(function (response) {
        vm.temp = response.data.temp;
        vm.hum = response.data.hum;
        vm.votes = response.data.votes;
        switch (response.data.status) {
          case 1:
            vm.status = "Votação Aberta"
            break;
         case 2:
            vm.status = "Ajustando Temperatura"
            break;
          default:
            vm.status = "Comece uma votação";
        }
      }, function () {
        console.log("Erro na requisição");
      });
    }
    function sendTemp() {
      var req = {
        method: 'POST',
        url: '/api/control',
        data: vm.tempControl
      };
      $http(req);
    }
    function sendVote(vote) {
      var req = {
        method: 'POST',
        url: '/api/vote',
        data: vote
      };
      $http(req);
    }
    vm.add = function () {
      vm.tempControl = vm.tempControl + 1;
      sendTemp();
    };
    vm.decrease = function () {
      vm.tempControl = vm.tempControl - 1;
      sendTemp();
    };

    vm.sendVote = function (temp) {
      vm.votes.push(temp);
      sendVote(temp);
    };
    vm.getVotes = function (type) {
      var count = 0;
      vm.votes.forEach(function (val) { 
        if(val == type) {
          count++;
        }
      });
      return count;
    }

    $interval(function () {
      getTemp();
    }, 1000);
  }]);