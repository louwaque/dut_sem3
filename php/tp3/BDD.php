<?php
require_once("configBDD.inc.php");

class BDD
{
  private $PDO;

  public function __construct()
  {
    try {
      $this->PDO = new PDO(DB_TYPE.':host='.DB_HOST.';port='.DB_PORT.';dbname='.DB_NAME, DB_USER, DB_PASS);
      $this->PDO->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
      $this->PDO->exec("SET NAMES 'utf8'");
    } catch (Exception $e) {
      $this->error($e);
    }
  }

  private function error(Exception $e)
  {
    echo 'Error: '.$e->getMessage().'<br>';
    echo 'N°: '.$e->getCode();
    exit();
  }

  public function getForms()
  {
    try {
      $query = $this->PDO->prepare("SELECT * FROM formulaire");
      $query->execute();
    } catch (Exception $e) {
      $this->error($e);
    }
    $res = $query->fetchAll(PDO::FETCH_ASSOC);

    return $res;
  }

  public function newForm($name, $description)
  {
    try {
      $query = $this->PDO->prepare("INSERT INTO formulaire (nom, description) values (?, ?)");
      $query->execute(array($name, $description));
    } catch (Exception $e) {
      $this->error($e);
    }
  }

  public function getQuestions($idForm)
  {
    try {
      $query = $this->PDO->prepare("SELECT * FROM question WHERE id_formulaire = ?");
      $query->execute(array($idForm));
    } catch (Exception $e) {
      $this->error($e);
    }
    $res = $query->fetchAll(PDO::FETCH_ASSOC);

    return $res;
  }

  private function newQuestion($idForm, $title)
  {
    try {
      $query = $this->PDO->prepare("INSERT INTO question (id_formulaire, intitule) values (?, ?)");
      $query->execute(array($idForm, $title));
    } catch (Exception $e) {
      $this->error($e);
    }
  }

  public function newOpenQuestion($idForm, $title)
  {
    try {
      newQuestion($idForm, $title);
      //get id question
      $query = $this->PDO->prepare("INSERT INTO question_ouverte (id_question_ouverte) values(?)");
      $query->execute(array($idQuestion));
    } catch (Exception $e) {
      $this->error($e);
    }
  }
}
?>
