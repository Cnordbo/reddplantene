var valueElement;
var gauge;

//Oppgave 1: Legg inn URL til json-data feeden i ajax-kallet.
//Oppgave 2: Hent ut korrekt verdi som sendes inn til displayValue
//Oppgave 3: Definer grenseverdier for våt, fuktig og tørr utifra hva din sensor leser inn. Gjør dette i displayValue

$(document).ready(function() {
  valueElement = document.getElementById("value");

  gauge = new JustGage({
    id: "gauge",
    value: 0,
    min: 0,
    max: 510,
    title: "Fuktighet",
    levelColors: ["#a52a2a", "#00ff00", "#0080ff"]
  });

  getMoistureLevel();

  setInterval(function() {
    getMoistureLevel();
  }, 15000);
});

function getMoistureLevel() {
  $.ajax({
    url:
      "https://api.thingspeak.com/channels/<channel>/fields/1.json?api_key=<api-key>&results=1"
  }).done(function(data) {
    displayValue(data.feeds[0].field1);
  });
}

function displayValue(value) {
  if (value > 350) {
    valueElement.innerHTML = "våt";
  } else if (value <= 350 && value > 150) {
    valueElement.innerHTML = "fuktig";
  } else if (value <= 150) {
    valueElement.innerHTML = "tørr";
  }

  updateGauge(value);
}

function updateGauge(value) {
  gauge.refresh(value);
}
