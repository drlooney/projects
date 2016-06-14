-- phpMyAdmin SQL Dump
-- version 3.5.8.2
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Czas wygenerowania: 01 Sie 2014, 11:58
-- Wersja serwera: 5.5.37-35.1-log
-- Wersja PHP: 5.4.29

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Baza danych: `holidayrp_mysql`
--

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `ipb_tickets`
--

CREATE TABLE IF NOT EXISTS `ipb_tickets` (
  `t_uid` int(5) unsigned zerofill NOT NULL AUTO_INCREMENT,
  `t_type` int(11) NOT NULL,
  `t_date` int(11) NOT NULL,
  `t_starter_id` int(11) NOT NULL,
  `t_topic` text NOT NULL,
  `t_start_message` text NOT NULL,
  `control` int(11) NOT NULL DEFAULT '1',
  `admin` int(11) NOT NULL,
  `status` int(11) NOT NULL,
  `last_reply` int(11) NOT NULL,
  PRIMARY KEY (`t_uid`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=8 ;

--
-- Struktura tabeli dla tabeli `ipb_tickets_post`
--

CREATE TABLE IF NOT EXISTS `ipb_tickets_post` (
  `t_uid` int(11) NOT NULL AUTO_INCREMENT,
  `ticket_uid` int(11) NOT NULL,
  `posts` text NOT NULL,
  `t_reply_id` int(11) NOT NULL,
  `date` int(11) NOT NULL,
  PRIMARY KEY (`t_uid`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=9 ;

--
-- Struktura tabeli dla tabeli `panel_admin_log`
--

CREATE TABLE IF NOT EXISTS `panel_admin_log` (
  `uid` int(11) NOT NULL AUTO_INCREMENT,
  `owner` int(11) NOT NULL,
  `log` text CHARACTER SET utf8 NOT NULL,
  `date` int(11) NOT NULL,
  `char` int(11) NOT NULL,
  PRIMARY KEY (`uid`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=179 ;

--
-- Struktura tabeli dla tabeli `panel_applications`
--

CREATE TABLE IF NOT EXISTS `panel_applications` (
  `a_uid` int(10) NOT NULL AUTO_INCREMENT,
  `pid` int(10) NOT NULL,
  `q1` tinyint(1) NOT NULL,
  `q2` tinyint(1) NOT NULL,
  `q3` tinyint(1) NOT NULL,
  `q4` tinyint(1) NOT NULL,
  `q5` tinyint(1) NOT NULL,
  `a1` text NOT NULL,
  `a2` text NOT NULL,
  `a3` text NOT NULL,
  `a4` text NOT NULL,
  `a5` text NOT NULL,
  `dateline` bigint(30) NOT NULL,
  `checkedby` int(10) NOT NULL,
  `notes` varchar(255) NOT NULL,
  `status` int(1) NOT NULL,
  `owner_app` int(11) NOT NULL,
  `kolejka` int(11) NOT NULL,
  PRIMARY KEY (`a_uid`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=27 ;

--
-- Struktura tabeli dla tabeli `panel_panel_log`
--

CREATE TABLE IF NOT EXISTS `panel_panel_log` (
  `uid` int(11) NOT NULL AUTO_INCREMENT,
  `owner` int(11) NOT NULL,
  `log` text CHARACTER SET utf8 NOT NULL,
  `date` int(11) NOT NULL,
  `char` int(11) NOT NULL,
  PRIMARY KEY (`uid`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=25 ;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `panel_premium_codes`
--

CREATE TABLE IF NOT EXISTS `panel_premium_codes` (
  `code_uid` int(11) NOT NULL AUTO_INCREMENT,
  `code_title` varchar(10) NOT NULL,
  `code_owner` int(11) NOT NULL,
  `code_date` int(11) NOT NULL,
  `typ` int(3) NOT NULL DEFAULT '0',
  PRIMARY KEY (`code_uid`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=163 ;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `panel_questions`
--

CREATE TABLE IF NOT EXISTS `panel_questions` (
  `uid` int(10) NOT NULL AUTO_INCREMENT,
  `question` varchar(255) NOT NULL,
  PRIMARY KEY (`uid`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=6 ;

--
-- Zrzut danych tabeli `panel_questions`
--

INSERT INTO `panel_questions` (`uid`, `question`) VALUES
(1, 'Zostajesz zÅ‚apany przez przestÄ™pcÃ³w, broÅ„ jest skierowana w TwojÄ… stronÄ™. Jak siÄ™ zachowasz w wyÅ¼ej wymienionej sytuacji? óóóżżżżłłł');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
